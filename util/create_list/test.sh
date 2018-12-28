#!/usr/bin/env sh
TOOL=./build/tools
LOG=log/log-$(date +%Y-%m-%d-%H-%M).log
#./build/tools/caffe train --solver=examples/mnist/lenet_solver_jwq01.prototxt -gpu all 2>&1 |tee $LOG
./build/tools/caffe test -model /home/user/software/caffe-master/models/juwenqi_dm_v3/inception_v3_train_test.prototxt   -weights   /home/user/software/caffe-master/models/15_v3_iter_50000.caffemodel  -iterations 10 --gpu=0 
