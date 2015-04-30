#!/usr/bin/env sh

TOOLS=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n/build/tools

GLOG_logtostderr=1 $TOOLS/finetune_net.bin    /nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n/funcprototxt/3dfunc_win_4_3d/seg_solver_2fc_3dnormal.prototxt /nfs/ladoga_no_backups/users/xiaolonw/seg_cls/sliding_window/models/3dnormal_win_cls_denoise_fc2/3dnormal__iter_280000

