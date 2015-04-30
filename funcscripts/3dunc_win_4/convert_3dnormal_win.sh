#!/usr/bin/env sh

rootfolder=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n

GLOG_logtostderr=1 $rootfolder/build/examples/3dnormal/convert_normal.bin  /home/xiaolonw/affordance/cls4/   /home/xiaolonw/affordance/cls4/trainLabels.txt  /home/xiaolonw/affordance/leveldb/func_win_4/3d_train_db 0 1 55 55
