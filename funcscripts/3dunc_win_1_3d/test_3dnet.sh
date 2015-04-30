#!/usr/bin/env sh                                                                                                

# test_net_seg.bin test_proto pre_train_model label.txt outputfolder [CPU/GPU]

ROOTFILE=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n

GLOG_logtostderr=1  /nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n/build/tools/test_net_3dnormal_win_func.bin /nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n/funcprototxt/3dfunc_win/seg_test_2fc_3dnormal.prototxt    /home/xiaolonw/affordance/models/func_win_1_3d/3dnormal__iter_320000  /home/xiaolonw/affordance/testLabels.txt  /home/xiaolonw/affordance/testresults/cls1_3d/



