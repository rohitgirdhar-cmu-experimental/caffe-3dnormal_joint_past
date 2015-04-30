#!/usr/bin/env sh

rootfolder=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n

GLOG_logtostderr=1 $rootfolder/build/examples/seg/convert_normal_reg55.bin  /nfs/ladoga_no_backups/users/xiaolonw/oedata/image_crop   /nfs/ladoga_no_backups/users/xiaolonw/oedata/segfile50.txt   /nfs/ladoga_no_backups/users/xiaolonw/oedata/leveldb/seg_train_db50 0 1 55 55
