#!/usr/bin/env sh

rootfolder=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n

GLOG_logtostderr=1 $rootfolder/build/examples/3dnormal/convert_normal.bin  /home/xiaolonw/affordance/cls4/   /home/xiaolonw/affordance/cls4/trainLabels.txt  /nfs/hn38/users/xiaolonw/affordance/func_win_4_imagenet  0 1 227 227
