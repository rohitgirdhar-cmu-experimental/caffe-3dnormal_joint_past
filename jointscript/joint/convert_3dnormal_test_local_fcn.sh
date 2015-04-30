#!/usr/bin/env sh

rootfolder=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_joint

GLOG_logtostderr=1 $rootfolder/build/examples/3dnormal/convert_normal_test.bin /nfs/hn46/xiaolonw/cnncode/viewer/croptest/ /nfs/hn46/xiaolonw/cnncode/viewer/testLabels.txt  /nfs/ladoga_no_backups/users/xiaolonw/3dnormal_fcn/leveldb/3d_test_db_small_large 0 0 260 195
