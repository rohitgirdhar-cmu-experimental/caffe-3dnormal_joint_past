#!/usr/bin/env sh

TOOLS=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n/build/tools

GLOG_logtostderr=1 $TOOLS/train_net.bin    /nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n/funcprototxt/3dfunc_win_2/seg_solver_2fc_3dnormal.prototxt

