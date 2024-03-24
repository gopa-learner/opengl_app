#! /usr/bin/bash

clear;

cd build/


echo "===========================================running make =======================================";

make -j4;

./OPENGL_BEENCOOK
