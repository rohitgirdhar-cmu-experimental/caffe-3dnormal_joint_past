#!/usr/bin/env sh

rootfolder=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n

GLOG_logtostderr=1 $rootfolder/build/examples/seg/convert_normal.bin /nfs/ladoga_no_backups/users/xiaolonw/oedata/image   /nfs/ladoga_no_backups/users/xiaolonw/oedata/bboxfile.txt  /nfs/ladoga_no_backups/users/xiaolonw/oedata/leveldb/loc_train_db 0 1 227 227






