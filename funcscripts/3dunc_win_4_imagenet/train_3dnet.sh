#!/usr/bin/env sh

TOOLS=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n/build/tools

GLOG_logtostderr=1 $TOOLS/finetune_net.bin    /nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n/funcprototxt/3dfunc_win_4_imagenet/seg_solver_2fc_3dnormal.prototxt /nfs/hn38/users/xiaolonw/affordance/imagenet_model/caffe_reference_imagenet_model

