// Copyright 2014 BVLC and contributors.

#include <stdint.h>
#include <leveldb/db.h>
#include <pthread.h>

#include <string>
#include <vector>
#include <iostream>  // NOLINT(readability/streams)
#include <fstream>  // NOLINT(readability/streams)
#include <utility>

#include "caffe/layer.hpp"
#include "caffe/util/io.hpp"
#include "caffe/util/math_functions.hpp"
#include "caffe/util/rng.hpp"
#include "caffe/vision_layers.hpp"


#include <cv.h>
#include <highgui.h>
#include <cxcore.h>


using std::iterator;
using std::string;
using std::pair;


using namespace cv;

namespace caffe {



bool LocReadImageToDatum(const vector<string>& files, const int height, const int width, Datum* datum)
{

	// files:
	// image, normals * n, labels

  cv::Mat cv_img;
  string filename;
  if (height > 0 && width > 0)
  {
	filename = files[0];
    cv::Mat cv_img_origin = cv::imread(filename, CV_LOAD_IMAGE_COLOR);
    cv::resize(cv_img_origin, cv_img,  cv::Size(width, height));
  }
  else
  {
	  LOG(ERROR) << "Could not open or find file " << filename;
	  return false;
  }

  if (!cv_img.data)
  {
    LOG(ERROR) << "Could not open or find file " << filename;
    return false;
  }

  // the last file is label
  int filenum = files.size() - 1;


	datum->set_channels(3 * filenum);
	datum->set_height(cv_img.rows);
	datum->set_width(cv_img.cols);
	datum->clear_label();
	datum->clear_data();
	datum->clear_float_data();

	for (int c = 0; c < 3; ++c) {
		for (int h = 0; h < cv_img.rows; ++h) {
		  for (int w = 0; w < cv_img.cols; ++w) {
			datum->add_float_data(static_cast<char>(cv_img.at<cv::Vec3b>(h, w)[c]));
		  }
		}
	}

	for(int i = 1; i < filenum; i ++)
	{
		string filename2 = files[i];
		FILE *pFile = fopen(filename2.c_str(), "rb");
		for (int c = 0; c < 3; ++c)
		{
			for (int h = 0; h < cv_img.rows; ++h)
			{
			  for (int w = 0; w < cv_img.cols; ++w)
			  {
				  float tnum;
				  fread(&tnum, sizeof(float), 1, pFile);
				  datum->add_float_data(tnum);
		//		imgIn.at<cv::Vec3b>(h, w)[2 - c] = (uchar)(tnum);
			  }
			}
		}
		fclose(pFile);
	}

  int num, cnt = 0;
  string labelfile = files[filenum];
  FILE *fid = fopen(labelfile.c_str(), "r");
  while(fscanf(fid, "%d", &num) > 0)
  {
	  datum->add_label(num);
	  cnt ++;
  }
  fclose(fid);


  return true;
}

template<typename Dtype>
void* ImageLocDataLayerPrefetch(void* layer_pointer)
{
	CHECK(layer_pointer);
	ImageLocDataLayer<Dtype>* layer =
			reinterpret_cast<ImageLocDataLayer<Dtype>*>(layer_pointer);
	CHECK(layer);
	Datum datum;
	CHECK(layer->prefetch_data_);
	Dtype* top_data = layer->prefetch_data_->mutable_cpu_data();
	Dtype* top_label = layer->prefetch_label_->mutable_cpu_data();
	ImageLocDataParameter image_loc_data_param =
			layer->layer_param_.image_loc_data_param();
	const Dtype scale = image_loc_data_param.scale();
	const int batch_size = image_loc_data_param.batch_size();
	const int crop_size = image_loc_data_param.crop_size();
	const bool mirror = image_loc_data_param.mirror();
	const int new_height = image_loc_data_param.new_height();
	const int new_width = image_loc_data_param.new_width();

	if (mirror && crop_size == 0)
	{
		LOG(FATAL)
				<< "Current implementation requires mirror and crop_size to be "
				<< "set at the same time.";
	}
	// datum scales
	const int channels = layer->datum_channels_;
	const int height = layer->datum_height_;
	const int width = layer->datum_width_;
	const int size = layer->datum_size_;
	const int lines_size = layer->lines_.size();
	const Dtype* mean = layer->data_mean_.cpu_data();


	if (!LocReadImageToDatum(layer->lines_[layer->lines_id_],new_height, new_width,
					&datum))
	{
		string filename = layer->lines_[layer->lines_id_][0];
		LOG(ERROR) << "Could not fretch file " << filename;
		return reinterpret_cast<void*>(NULL);
	}
	//const string& data = datum.data();
	const int slide_stride = image_loc_data_param.slide_stride();


	int hnum = new_height / slide_stride;
	int wnum = new_width  / slide_stride;
	CHECK_EQ(hnum * wnum, batch_size);
	int item_id = 0;
	for(int gh = 0; gh < hnum; gh ++ )
		for(int gw = 0; gw < wnum; gw ++)
		{
      char ss1[1010];
      sprintf(ss1,"/home/dragon123/cnncode/showimg/%d.jpg",item_id);
      Mat img(Size(55,55),CV_8UC3);

			int midh = gh * slide_stride + slide_stride / 2;
			int midw = gw * slide_stride + slide_stride / 2;
			int h_off = midh - crop_size / 2;
			int w_off = midw - crop_size / 2;

			// Normal copy
			for (int c = 0; c < channels; ++c)
			{
				for (int h = 0; h < crop_size; ++h)
				{
					for (int w = 0; w < crop_size; ++w)
					{
						int top_index = ((item_id * channels + c)
								* crop_size + h) * crop_size + w;
						int data_index = (c * height + h + h_off) * width
								+ w + w_off;
						int mean_index = ( c * crop_size + h) * crop_size + w;

						Dtype datum_element = 0;
						if(h + h_off >=0 && h + h_off < new_height && w + w_off >=0 && w + w_off < new_width)
							datum_element = datum.float_data(data_index);
							//datum_element =	static_cast<Dtype>(static_cast<uint8_t>(data[data_index]));
						//top_data[top_index] = (datum_element - mean[data_index]) * scale;
						top_data[top_index] = (datum_element - mean[mean_index]) * scale;

            img.at<cv::Vec3b>(h, w)[c] = (uchar)(datum_element * scale);
            
					}
				}
			}

      imwrite(ss1,img);

			//top_labelreinterpret_cast[item_id] = datum.label();
			for (int label_i = 0; label_i < datum.label_size(); label_i++)
			{
				top_label[item_id * datum.label_size() + label_i] = datum.label(label_i);
			}
			item_id ++;
		}

		// go to the next iter
		layer->lines_id_++;
		if (layer->lines_id_ >= lines_size)
		{
			// We have reached the end. Restart from the first.
			DLOG(INFO) << "Restarting data prefetching from start.";
			layer->lines_id_ = 0;
			if (layer->layer_param_.image_loc_data_param().shuffle())
			{
				layer->ShuffleImages();
			}
		}

		return reinterpret_cast<void*>(NULL);
}

template <typename Dtype>
ImageLocDataLayer<Dtype>::~ImageLocDataLayer<Dtype>() {
  JoinPrefetchThread();
}

template <typename Dtype>
void ImageLocDataLayer<Dtype>::SetUp(const vector<Blob<Dtype>*>& bottom,
      vector<Blob<Dtype>*>* top) {
  CHECK_EQ(bottom.size(), 0) << "Input Layer takes no input blobs.";
  CHECK_EQ(top->size(), 2) << "Input Layer takes two blobs as output.";
  const int new_height  = this->layer_param_.image_loc_data_param().new_height();
  const int new_width  = this->layer_param_.image_loc_data_param().new_height();

  const int slide_stride = this->layer_param_.image_loc_data_param().slide_stride();
  const int source_num = this->layer_param_.image_loc_data_param().source_num();

  CHECK((new_height == 0 && new_width == 0) ||
      (new_height > 0 && new_width > 0)) << "Current implementation requires "
      "new_height and new_width to be set at the same time.";
  // Read the file with filenames and labels
  const string& source = this->layer_param_.image_loc_data_param().source();
  LOG(INFO) << "Opening file " << source;
  std::ifstream infile(source.c_str());
  string filename;
  // source_num files + 1 label file
  while (infile >> filename) {
	vector<string> ts;
	ts.push_back(filename);
    for (int i = 0; i < source_num; i ++)
    {
    	infile >> filename;
    	ts.push_back(filename);
    }
    lines_.push_back(ts);

  }

  if (this->layer_param_.image_loc_data_param().shuffle()) {
    // randomly shuffle data
    LOG(INFO) << "Shuffling data";
    const unsigned int prefetch_rng_seed = caffe_rng_rand();
    prefetch_rng_.reset(new Caffe::RNG(prefetch_rng_seed));
    ShuffleImages();
  }
  LOG(INFO) << "A total of " << lines_.size() << " images.";

  lines_id_ = 0;
  // Check if we would need to randomly skip a few data points
  if (this->layer_param_.image_loc_data_param().rand_skip()) {
    unsigned int skip = caffe_rng_rand() %
        this->layer_param_.image_loc_data_param().rand_skip();
    LOG(INFO) << "Skipping first " << skip << " data points.";
    CHECK_GT(lines_.size(), skip) << "Not enough points to skip";
    lines_id_ = skip;
  }
  // Read a data point, and use it to initialize the top blob.
  Datum datum;
  CHECK(LocReadImageToDatum(lines_[lines_id_],
                         new_height, new_width, &datum));
  // image
  const int crop_size = this->layer_param_.image_loc_data_param().crop_size();
  const int batch_size = this->layer_param_.image_loc_data_param().batch_size();
  const string& mean_file = this->layer_param_.image_loc_data_param().mean_file();
  if (crop_size > 0) {
    (*top)[0]->Reshape(batch_size, datum.channels(), crop_size, crop_size);
    prefetch_data_.reset(new Blob<Dtype>(batch_size, datum.channels(),
                                         crop_size, crop_size));
  } else {
    (*top)[0]->Reshape(batch_size, datum.channels(), datum.height(),
                       datum.width());
    prefetch_data_.reset(new Blob<Dtype>(batch_size, datum.channels(),
                                         datum.height(), datum.width()));
  }
  LOG(INFO) << "output data size: " << (*top)[0]->num() << ","
      << (*top)[0]->channels() << "," << (*top)[0]->height() << ","
      << (*top)[0]->width();
  // label
  (*top)[1]->Reshape(batch_size, 1, 1, 1);
  prefetch_label_.reset(new Blob<Dtype>(batch_size, 1, 1, 1));
  // datum size
  datum_channels_ = datum.channels();
  datum_height_ = datum.height();
  datum_width_ = datum.width();
  datum_size_ = datum.channels() * datum.height() * datum.width();
  //CHECK_GT(datum_height_, crop_size);
  //CHECK_GT(datum_width_, crop_size);
  // check if we want to have mean
  if (this->layer_param_.image_loc_data_param().has_mean_file()) {
    BlobProto blob_proto;
    LOG(INFO) << "Loading mean file from" << mean_file;
    ReadProtoFromBinaryFile(mean_file.c_str(), &blob_proto);
    data_mean_.FromProto(blob_proto);
    //CHECK_EQ(data_mean_.num(), 1);
    //CHECK_EQ(data_mean_.channels(), datum_channels_);
    //CHECK_EQ(data_mean_.height(), crop_size);
    //CHECK_EQ(data_mean_.width(), crop_size);
  } else {
    // Simply initialize an all-empty mean.
    data_mean_.Reshape(1, datum_channels_, crop_size, crop_size);
  }
  // Now, start the prefetch thread. Before calling prefetch, we make two
  // cpu_data calls so that the prefetch thread does not accidentally make
  // simultaneous cudaMalloc calls when the main thread is running. In some
  // GPUs this seems to cause failures if we do not so.
  prefetch_data_->mutable_cpu_data();
  prefetch_label_->mutable_cpu_data();
  data_mean_.cpu_data();
  DLOG(INFO) << "Initializing prefetch";
  CreatePrefetchThread();
  DLOG(INFO) << "Prefetch initialized.";
}

template <typename Dtype>
void ImageLocDataLayer<Dtype>::CreatePrefetchThread() {
  phase_ = Caffe::phase();
  const bool prefetch_needs_rand =
      this->layer_param_.image_loc_data_param().shuffle() ||
          ((phase_ == Caffe::TRAIN) &&
           (this->layer_param_.image_loc_data_param().mirror() ||
            this->layer_param_.image_loc_data_param().crop_size()));
  if (prefetch_needs_rand) {
    const unsigned int prefetch_rng_seed = caffe_rng_rand();
    prefetch_rng_.reset(new Caffe::RNG(prefetch_rng_seed));
  } else {
    prefetch_rng_.reset();
  }
  // Create the thread.
  CHECK(!pthread_create(&thread_, NULL, ImageLocDataLayerPrefetch<Dtype>,
        static_cast<void*>(this))) << "Pthread execution failed.";
}

template <typename Dtype>
void ImageLocDataLayer<Dtype>::ShuffleImages() {
  const int num_images = lines_.size();
  for (int i = 0; i < num_images; ++i) {
    const int max_rand_index = num_images - i;
    const int rand_index = PrefetchRand() % max_rand_index;
    vector<string> item = lines_[rand_index];
    lines_.erase(lines_.begin() + rand_index);
    lines_.push_back(item);
  }
}

template <typename Dtype>
void ImageLocDataLayer<Dtype>::JoinPrefetchThread() {
  CHECK(!pthread_join(thread_, NULL)) << "Pthread joining failed.";
}

template <typename Dtype>
unsigned int ImageLocDataLayer<Dtype>::PrefetchRand() {
  caffe::rng_t* prefetch_rng =
      static_cast<caffe::rng_t*>(prefetch_rng_->generator());
  return (*prefetch_rng)();
}

template <typename Dtype>
Dtype ImageLocDataLayer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,
      vector<Blob<Dtype>*>* top) {
  // First, join the thread
  JoinPrefetchThread();
  // Copy the data
  caffe_copy(prefetch_data_->count(), prefetch_data_->cpu_data(),
             (*top)[0]->mutable_cpu_data());
  caffe_copy(prefetch_label_->count(), prefetch_label_->cpu_data(),
             (*top)[1]->mutable_cpu_data());
  // Start a new prefetch thread
  CreatePrefetchThread();
  return Dtype(0.);
}

INSTANTIATE_CLASS(ImageLocDataLayer);

}  // namespace caffe
