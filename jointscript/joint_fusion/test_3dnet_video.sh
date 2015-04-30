#!/usr/bin/env sh                                                                                                

# test_net_seg.bin test_proto pre_train_model label.txt outputfolder [CPU/GPU]

ROOTFILE=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_joint

GLOG_logtostderr=1  $ROOTFILE/build_compute-0-5/tools/test_net_3dnormal_joint_img.bin /nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_joint/jointscript/joint_fusion/seg_test_3dnormal_joint_video.prototxt   /nfs/hn38/users/xiaolonw/3d_fcn_data/models/3dnormal__0_iter_28000  /nfs/hn38/users/xiaolonw/3d_fcn_data/models/3dnormal__1_iter_28000  /nfs/hn38/users/xiaolonw/3d_fcn_data/models/3dnormal__2_iter_28000  /nfs/hn46/xiaolonw/cnncode/viewer/makevideo/testLabels.txt  /nfs/hn38/users/xiaolonw/3d_fcn_data/results



