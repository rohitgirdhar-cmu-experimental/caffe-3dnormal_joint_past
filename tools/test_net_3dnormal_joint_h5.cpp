// 输出分割的结果

/*#include <cuda_runtime.h>*/

#include <opencv2/opencv.hpp>

/*#include <cv.h>
#include <highgui.h>
#include <cxcore.h>*/

#include <cstring>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <utility>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <iostream>

#include <leveldb/db.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "caffe/caffe.hpp"
#include "caffe/util/io.hpp"

#include <string>
#include <fstream>

#include <hdf5.h>

#define NORMALS_DIM (195 * 260 * 3)

using namespace std;
using namespace cv;
using namespace caffe;
using std::vector;

int CreateDir(const char *sPathName, int beg) {
	char DirName[256];
	strcpy(DirName, sPathName);
	int i, len = strlen(DirName);
	if (DirName[len - 1] != '/')
		strcat(DirName, "/");

	len = strlen(DirName);

	for (i = beg; i < len; i++) {
		if (DirName[i] == '/') {
			DirName[i] = 0;
			if (access(DirName, 0) != 0) {
				CHECK(mkdir(DirName, 0755) == 0)<< "Failed to create folder "<< sPathName;
			}
			DirName[i] = '/';
		}
	}

	return 0;
}

char buf[101000];
int main(int argc, char** argv)
{

	//cudaSetDevice(0);
	Caffe::set_phase(Caffe::TEST);
	//Caffe::SetDevice(2);
	if (argc == 8 && strcmp(argv[7], "CPU") == 0) {
		LOG(ERROR) << "Using CPU";
		Caffe::set_mode(Caffe::CPU);
	} else {
		LOG(ERROR) << "Using GPU";
		Caffe::set_mode(Caffe::GPU);
    if (argc == 9) {
  	  Caffe::SetDevice(atoi(argv[8]));
    } else {
  	  Caffe::SetDevice(0);
    }
	}

	//Caffe::set_mode(Caffe::CPU);

	NetParameter test_net_param;
	ReadProtoFromTextFile(argv[1], &test_net_param);
	Net<float> caffe_test_net(test_net_param);

	for(int i = 0; i < 3; i ++)
	{
		NetParameter trained_net_param;
		ReadProtoFromBinaryFile(argv[2 + i], &trained_net_param);
		caffe_test_net.CopyTrainedLayersFrom(trained_net_param);
	}

	vector<shared_ptr<Layer<float> > > layers = caffe_test_net.layers();
	//const DataLayer<float> *datalayer = dynamic_cast<const DataLayer<float>* >(layers[0].get());
	//CHECK(datalayer);

	string labelFile(argv[3 + 2]);
	int data_counts = 0;
	FILE * file1 = fopen(labelFile.c_str(), "r");
	while(fgets(buf,100000,file1) > 0)
	{
		data_counts++;
	}
	fclose(file1);

	vector<Blob<float>*> dummy_blob_input_vec;
	string rootfolder(argv[4 + 2]);
	rootfolder.append("/");
	CreateDir(rootfolder.c_str(), rootfolder.size() - 1);
	string folder;
	string fName;

	float output;
	int counts = 0;


	Blob<float>* c1 = (*(caffe_test_net.bottom_vecs().rbegin()))[0];
  int c2 = c1->num();
	int batchCount = std::ceil(data_counts / (floor)(c2));//(test_net_param.layers(0).layer().batchsize()));//                (test_net_param.layers(0).layer().batchsize() ));

	string resultfpath = rootfolder + "/3dNormalResult.h5";

  hid_t file = H5Fcreate(resultfpath.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
  hsize_t dims[2] = {data_counts, NORMALS_DIM};
  hid_t file_space = H5Screate_simple(2, dims, NULL);
  hid_t plist = H5Pcreate(H5P_DATASET_CREATE);
  H5Pset_layout(plist, H5D_CHUNKED);
  hsize_t chunk_dims[2] = {10, NORMALS_DIM};
  H5Pset_chunk(plist, 2, chunk_dims);
  H5Pset_deflate(plist, 6);
  hid_t dset = H5Dcreate(file, "normals", H5T_NATIVE_FLOAT, file_space, H5P_DEFAULT, plist, H5P_DEFAULT);
  H5Pclose(plist);
  H5Sclose(file_space);
  dims[0] = 1; dims[1] = NORMALS_DIM;
  hid_t mem_space = H5Screate_simple(2, dims, NULL);


	for (int batch_id = 0; batch_id < batchCount; ++batch_id)
	{
		LOG(INFO)<< "processing batch :" << batch_id+1 << "/" << batchCount <<"...";

		const vector<Blob<float>*>& result = caffe_test_net.Forward(dummy_blob_input_vec);
		Blob<float>* bboxs = (*(caffe_test_net.bottom_vecs().rbegin()))[0];
		int bsize = bboxs->num();

		const Blob<float>* labels = (*(caffe_test_net.bottom_vecs().rbegin()))[1];
		for (int i = 0; i < bsize && counts < data_counts; i++, counts++)
		{
			int channels = bboxs->channels();
			int height   = bboxs->height();
			int width    = bboxs->width();
			int len = channels * height * width;
			Mat imgout(Size(width, height), CV_32FC3);

      float *imgout_arr = new float[width * height * channels];
			int pos = 0;
      for (int c = 0; c < channels; c ++)
				for(int h = 0; h < height; h ++)
					for(int w = 0; w < width; w ++)
					{
						imgout_arr[pos++] = (float)(bboxs->data_at(i, c, h, w));
					}
 
      // select the hyperslab
      file_space = H5Dget_space(dset);
      hsize_t start[2] = {batch_id * bsize + i, 0};
      hsize_t count[2] = {1, NORMALS_DIM};
      H5Sselect_hyperslab(file_space, H5S_SELECT_SET, start, NULL, count, NULL);
      H5Dwrite(dset, H5T_NATIVE_FLOAT, mem_space, file_space, H5P_DEFAULT, imgout_arr);
      H5Sclose(file_space);
      delete[] imgout_arr;
		}
	}
  H5Sclose(mem_space);
  H5Dclose(dset);
  H5Fclose(file);

	return 0;
}
