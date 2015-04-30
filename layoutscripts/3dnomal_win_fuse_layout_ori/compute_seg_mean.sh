#!/usr/bin/env sh

rootfolder=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n

GLOG_logtostderr=1 $rootfolder/build/tools/demo_compute_image_mean_float.bin /home/xiaolonw/3ddata/coarse_layout_result/leveldb_fuse/3d_train_db_coarselayout_ori /home/xiaolonw/3ddata/coarse_layout_result/leveldb_fuse/3d_train_db_coarselayout_ori/3d_mean.binaryproto
