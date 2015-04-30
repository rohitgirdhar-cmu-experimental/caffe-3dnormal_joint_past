#!/usr/bin/env sh

rootfolder=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n
sourcefolder=/nfs/ladoga_no_backups/users/xiaolonw/seg_cls/sliding_window_edge_high_test


GLOG_logtostderr=1 $rootfolder/build_balaton/examples/3dnormal/convert_normal_win_high_van_test.bin $sourcefolder/images/ $sourcefolder/locs/testLoc3.txt  $sourcefolder/leveldb_fusetest/3d_test_layout_ori_db3 0 0 55 55 $sourcefolder/reg_coarse_tri $sourcefolder/reg_localedge_tri/  $sourcefolder/reg_layout_coarse/





