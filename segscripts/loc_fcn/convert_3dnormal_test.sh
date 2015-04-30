#!/usr/bin/env sh

rootfolder=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n

GLOG_logtostderr=1 $rootfolder/build/examples/seg/convert_normal_test.bin  /nfs/ladoga_no_backups/users/xiaolonw/oedata/image/  /nfs/ladoga_no_backups/users/xiaolonw/oedata/test.txt  /nfs/ladoga_no_backups/users/xiaolonw/oedata/leveldb/3d_test_db_small_350 0 0 350 350
