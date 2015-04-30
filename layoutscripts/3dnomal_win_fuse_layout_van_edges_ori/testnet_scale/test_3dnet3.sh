#!/usr/bin/env sh                                                                                                

# test_net_seg.bin test_proto pre_train_model label.txt outputfolder [CPU/GPU]

ROOTFILE=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n

GLOG_logtostderr=1  $ROOTFILE/build/tools/test_net_3dnormal_high_scale.bin $ROOTFILE/layoutprototxt/3dnomal_win_fuse_layout_van_edges_ori_scale/seg_test_2fc_3dnormal3.prototxt /home/xiaolonw/3ddata/coarse_layout_result/models/3dnomal_win_fuse_layout_van_edges_ori_2/3dnormal__iter_180000  /nfs/ladoga_no_backups/users/xiaolonw/seg_cls/sliding_window_edge_high_test_scale/locs/testLoc3.txt /nfs/hn38/users/xiaolonw/sliding_window_edge_high_test_scale/results/3d_fuse_ori_3


