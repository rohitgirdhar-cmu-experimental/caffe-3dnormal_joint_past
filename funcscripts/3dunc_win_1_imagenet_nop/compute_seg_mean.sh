#!/usr/bin/env sh

rootfolder=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n

GLOG_logtostderr=1 $rootfolder/build_onega/tools/demo_compute_image_mean.bin /nfs/hn38/users/xiaolonw/affordance/func_win_1_imagenet/3d_train_db   /nfs/hn38/users/xiaolonw/affordance/func_win_1_imagenet/3d_train_db/3d_mean.binaryproto
