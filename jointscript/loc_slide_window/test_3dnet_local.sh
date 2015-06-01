#!/usr/bin/env sh                                                                                                

# test_net_seg.bin test_proto pre_train_model label.txt outputfolder [CPU/GPU]

ROOTFILE=/home/dragon123/3dnormal_joint_cnncode/caffe-3dnormal_joint

GLOG_logtostderr=1  /home/dragon123/3dnormal_joint_cnncode/caffe-3dnormal_joint_past/build/tools/test_net_3dnormal_locim.bin /home/dragon123/3dnormal_joint_cnncode/caffe-3dnormal_joint_past/jointscript/loc_slide_window/seg_test_2fc_3dnormal.prototxt /home/dragon123/3dnormal_joint_cnncode/models/win_local_model/3dnormal__iter_280000  /home/dragon123/3dnormal_joint_cnncode/imgfile.txt /home/dragon123/3dnormal_joint_cnncode/slide_results





