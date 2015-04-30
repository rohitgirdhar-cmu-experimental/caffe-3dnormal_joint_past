#!/usr/bin/env sh

rootfolder=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n

GLOG_logtostderr=1 $rootfolder/build/examples/3dnormal/convert_normal_functest.bin /nfs/ladoga_no_backups/users/xiaolonw/seg_cls/sliding_window/images_test/ /nfs/ladoga_no_backups/users/xiaolonw/seg_cls/sliding_window/testLabels_ran.txt  /home/xiaolonw/affordance/leveldb/3d_test_db_small_ran 0 0 55 55
