#!/usr/bin/env sh                                                                                                

# test_net_seg.bin test_proto pre_train_model label.txt outputfolder [CPU/GPU]

ROOTFILE=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n

GLOG_logtostderr=1  /nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n/build/tools/test_net_3dnormal_loc.bin /nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n/segscripts/loc/imagenet_test.prototxt    /nfs/ladoga_no_backups/users/xiaolonw/oedata/models/loc/loc__iter_200000   /nfs/ladoga_no_backups/users/xiaolonw/oedata/test.txt  /nfs/ladoga_no_backups/users/xiaolonw/oedata/testresults/  


