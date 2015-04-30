#!/usr/bin/env sh

rootfolder=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n
sourcefolder=/nfs/hn38/users/xiaolonw/ucb_test/ucb_fusion_test

GLOG_logtostderr=1 $rootfolder/build_onega/examples/3dnormal/convert_normal_win_high_5_test.bin $sourcefolder/images/ $sourcefolder/locs/testLoc2.txt  $sourcefolder/leveldb_fusetest/3d_test_5new_db2 0 0 55 55   $sourcefolder/reg_coarselay_tri_test/   $sourcefolder/reg_local_tri/  $sourcefolder/reg_coarse_van_tri/  $sourcefolder/reg_edges/  $sourcefolder/reg_layout_coarse/ 


