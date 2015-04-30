#!/usr/bin/env sh                                                                                                

# test_net_seg.bin test_proto pre_train_model label.txt outputfolder [CPU/GPU]

ROOTFILE=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n

GLOG_logtostderr=1  $ROOTFILE/build_compute-0-5/tools/test_net_3dnormal_high.bin $ROOTFILE/layoutprototxt/3dnomal_win_fuse_layout_van_edges_ucb/seg_test_2fc_3dnormal2.prototxt /home/xiaolonw/3ddata/coarse_layout_result/models/3dnomal_win_fuse_layout_van_edges_2/3dnormal__iter_240000  /nfs/hn38/users/xiaolonw/ucb_test/ucb_fusion_test/locs/testLoc2.txt  /nfs/hn38/users/xiaolonw/ucb_test/ucb_fusion_test/results/3d_fuse_2/



