#!/usr/bin/env sh                                                                                                

# test_net_seg.bin test_proto pre_train_model label.txt outputfolder [CPU/GPU]

ROOTFILE=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n

GLOG_logtostderr=1  /nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n/build/tools/test_net_3dnormal_seg.bin  /nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n/segscripts/seg3/seg_test_2fc_3dnormal.prototxt  /nfs/ladoga_no_backups/users/xiaolonw/oedata/models/seg3/seg__iter_150000  /nfs/ladoga_no_backups/users/xiaolonw/oedata/test.txt   /nfs/ladoga_no_backups/users/xiaolonw/oedata/testresults3/

