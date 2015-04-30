#!/usr/bin/env sh

rootfolder=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n

GLOG_logtostderr=1 $rootfolder/build/examples/seg/convert_normal_test.bin  /nfs/ladoga_no_backups/users/xiaolonw/oedata/gym/  /nfs/ladoga_no_backups/users/xiaolonw/oedata/gymtest.txt  /nfs/ladoga_no_backups/users/xiaolonw/oedata/leveldb/gym_test_227 0 0 227 227
