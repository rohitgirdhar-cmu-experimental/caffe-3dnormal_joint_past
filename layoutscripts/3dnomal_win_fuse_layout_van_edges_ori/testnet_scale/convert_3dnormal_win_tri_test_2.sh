#!/usr/bin/env sh

rootfolder=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n
sourcefolder=/nfs/hn38/users/xiaolonw/sliding_window_edge_high_test_scale
source2=/nfs/ladoga_no_backups/users/xiaolonw/seg_cls/sliding_window_edge_high_test_scale


GLOG_logtostderr=1 $rootfolder/build_onega/examples/3dnormal/convert_normal_win_high_5_test_scale.bin $source2/images/ $source2/locs/testLoc2.txt  $sourcefolder/leveldb_fusetest/3d_test_5_db2 0 0 55 55   $source2/reg_coarse_tri/   $sourcefolder/reg_localedge_tri/  $sourcefolder/reg_coarse_van_tri/  $sourcefolder/reg_edges/  $sourcefolder/reg_layout_coarse/ 



