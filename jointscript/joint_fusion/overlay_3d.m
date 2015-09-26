function overlay_3d()
datadir = '/home/rgirdhar/Work/Projects/004_PoseEst/tmp/dataset/';
resdir = '/home/rgirdhar/Work/Projects/004_PoseEst/tmp/results/';
outdir = '/home/rgirdhar/Work/Projects/004_PoseEst/tmp/overlayed/';

for i = 1 : 10
  I = imread(fullfile(datadir, [num2str(i) '.jpg']));
  S = imread(fullfile(resdir, [num2str(i) '.jpg']));
  S = imresize(S, [size(I, 1) size(I, 2)]);
  F = uint8(I * 0.4 + S * 0.6);
  imwrite(F, fullfile(outdir, [num2str(i) '.jpg']));
end

