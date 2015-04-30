#!/usr/bin/env sh

rootfolder=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n

GLOG_logtostderr=1 $rootfolder/build/examples/3dnormal/convert_normal_win_high_edge2_van.bin /nfs/ladoga_no_backups/users/xiaolonw/seg_cls/sliding_window_edge_high/images/ /nfs/ladoga_no_backups/users/xiaolonw/seg_cls/sliding_window_edge_high/trainLabels.txt  /home/xiaolonw/3ddata/coarse_layout_result/leveldb_fuse/3d_train_db_coarselayout_van_ori 0 1 55 55 /nfs/ladoga_no_backups/users/xiaolonw/seg_cls/sliding_window_edge_high/reg_coarse_tri /nfs/ladoga_no_backups/users/xiaolonw/seg_cls/sliding_window_edge_high/reg_local_edge_tri/  /nfs/ladoga_no_backups/users/xiaolonw/seg_cls/sliding_window_edge_high/reg_coarse_van_tri  /home/xiaolonw/3ddata/coarse_layout_result/reg_layout_tri/ 


