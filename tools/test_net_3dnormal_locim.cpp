// 输出分割的结果

/*#include <cuda_runtime.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>*/

#include <cv.h>
#include <highgui.h>
#include <cxcore.h>

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

using namespace std;
using namespace cv;
using namespace caffe;
using std::vector;

#define HEIGHT 195
#define WIDTH  260
#define STRIDE 13


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

	cudaSetDevice(0);
	Caffe::set_phase(Caffe::TEST);
	//Caffe::set_mode(Caffe::CPU);

	if (argc == 8 && strcmp(argv[7], "CPU") == 0) {
		LOG(ERROR) << "Using CPU";
		Caffe::set_mode(Caffe::CPU);
	} else {
		LOG(ERROR) << "Using GPU";
		Caffe::set_mode(Caffe::GPU);
	}

	Caffe::set_mode(Caffe::CPU);
//	Caffe::SetDevice(0);
	NetParameter test_net_param;
	ReadProtoFromTextFile(argv[1], &test_net_param);
	Net<float> caffe_test_net(test_net_param);
	NetParameter trained_net_param;
	ReadProtoFromBinaryFile(argv[2], &trained_net_param);
	caffe_test_net.CopyTrainedLayersFrom(trained_net_param);

	vector<shared_ptr<Layer<float> > > layers = caffe_test_net.layers();
	//const DataLayer<float> *datalayer = dynamic_cast<const DataLayer<float>* >(layers[0].get());
	//CHECK(datalayer);

	string labelFile(argv[3]);
	int data_counts = 0;
	FILE * file = fopen(labelFile.c_str(), "r");
	while(fgets(buf,100000,file) > 0)
	{
		data_counts++;
	}
	fclose(file);

	vector<Blob<float>*> dummy_blob_input_vec;
	string rootfolder(argv[4]);
	rootfolder.append("/");
	CreateDir(rootfolder.c_str(), rootfolder.size() - 1);
	string folder;
	string fName;

	float output;
	int counts = 0;

	file = fopen(labelFile.c_str(), "r");

	Blob<float>* c1 = (*(caffe_test_net.bottom_vecs().rbegin()))[0];
    int c2 = c1->num();
	int batchCount = data_counts;

	string resulttxt = rootfolder + "3dNormalResult.txt";
	FILE * resultfile = fopen(resulttxt.c_str(), "w");

	float * output_mat = new float[HEIGHT * WIDTH * 3];

	for (int batch_id = 0; batch_id < batchCount; ++batch_id)
	{
		LOG(INFO)<< "processing batch :" << batch_id+1 << "/" << batchCount <<"...";

		const vector<Blob<float>*>& result = caffe_test_net.Forward(dummy_blob_input_vec);
		Blob<float>* bboxs = (*(caffe_test_net.bottom_vecs().rbegin()))[0];
		int bsize = bboxs->num();

		const Blob<float>* labels = (*(caffe_test_net.bottom_vecs().rbegin()))[1];

		char fname[1010];
		char fname2[1010];
		fscanf(file, "%s", fname);
		for(int i = 0; i < 1; i ++ ) fscanf(file, "%s", fname2);
		fprintf(resultfile, "%s ", fname);

		int channels = bboxs->channels();
		int height   = bboxs->height();
		int width    = bboxs->width();
		int hnum = HEIGHT / STRIDE;
		int wnum = WIDTH / STRIDE;
		int stride = STRIDE;
		for(int i = 0; i < bsize; i++)
		for(int c = 0; c < channels; c ++)
		{
			int hi = i / wnum;
			int wi = i % wnum;
			int off_h = hi * stride;
			int off_w = wi * stride;
			for(int h = 0; h < height; h ++)
				for(int w = 0; w < width; w ++)
					{
						// output_mat[c * HEIGHT * WIDTH + (off_w + w) * HEIGHT + off_h + h ] = (float)(bboxs->data_at(i, c, h, w));
						fprintf(resultfile, "%f ", (float)(bboxs->data_at(i, c, h, w)) );
					}
			fprintf(resultfile, "\n");
		}
		//for(int i = 0; i < HEIGHT * WIDTH * 3; i ++) 
		//	fprintf(resultfile, "%f ", output_mat[i] );
		//fprintf(resultfile, "\n");


	}

	delete output_mat;

	fclose(resultfile);
	fclose(file);


	return 0;
}
