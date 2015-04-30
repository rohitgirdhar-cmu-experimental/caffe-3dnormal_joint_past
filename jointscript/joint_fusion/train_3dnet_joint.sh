#!/usr/bin/env sh

TOOLS=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_joint/build/tools

modelsource=/nfs/ladoga_no_backups/users/xiaolonw/3dnormal_fcn/pretrain_models

GLOG_logtostderr=1 $TOOLS/finetune_net.bin   /nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_joint/jointscript/joint_fusion/seg_solver_3dnormal_joint.prototxt $modelsource/3dnormal_global_full  $modelsource/3dnormal_local_full  $modelsource/3dnormal_fusion_full



