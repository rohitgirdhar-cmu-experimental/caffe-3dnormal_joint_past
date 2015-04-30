#!/usr/bin/env sh

TOOLS=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_joint/build/tools

modelsource=/nfs/ladoga_no_backups/users/xiaolonw/3dnormal_fcn/pretrain_models

GLOG_logtostderr=1 $TOOLS/finetune_net.bin   /nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_joint/jointscript/joint_fusion/seg_solver_3dnormal_joint.prototxt /nfs/hn38/users/xiaolonw/3d_fcn_data/models/3dnormal__0_iter_36000  /nfs/hn38/users/xiaolonw/3d_fcn_data/models/3dnormal__1_iter_36000  /nfs/hn38/users/xiaolonw/3d_fcn_data/models/3dnormal__2_iter_36000


