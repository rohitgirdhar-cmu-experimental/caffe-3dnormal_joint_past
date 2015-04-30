#!/usr/bin/env sh

TOOLS=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n/build/tools

GLOG_logtostderr=1 $TOOLS/train_net.bin   /nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n/layoutprototxt/3dnomal_win_fuse_layout_van_edges/seg_solver_2fc_3dnormal.prototxt  /home/xiaolonw/3ddata/coarse_layout_result/models/3dnomal_win_fuse_layout_van_edges/3dnormal__iter_60000.solverstate


 
