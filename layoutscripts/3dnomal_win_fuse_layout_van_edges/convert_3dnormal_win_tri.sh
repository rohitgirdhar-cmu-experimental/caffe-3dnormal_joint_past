#!/usr/bin/env sh

rootfolder=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n

GLOG_logtostderr=1 $rootfolder/build/examples/3dnormal/convert_normal_win_high_5.bin /nfs/ladoga_no_backups/users/xiaolonw/seg_cls/sliding_window_edge_high/images/ /nfs/ladoga_no_backups/users/xiaolonw/seg_cls/sliding_window_edge_high/trainLabels.txt  /home/xiaolonw/3ddata/coarse_layout_result/leveldb_fuse/3d_train_db_coarselayout_van_edges 0 1 55 55 /home/xiaolonw/3ddata/coarse_layout_result/reg_coarselay_tri  /nfs/ladoga_no_backups/users/xiaolonw/seg_cls/sliding_window_edge_high/reg_local_edge_tri/  /home/xiaolonw/3ddata/coarse_layout_result/reg_coarselayout_van_tri/  /nfs/ladoga_no_backups/users/xiaolonw/seg_cls/sliding_window_edge_high/reg_edges   /home/xiaolonw/3ddata/coarse_layout_result/reg_layout_tri/ 



