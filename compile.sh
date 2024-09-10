#! /usr/bin/bash

clear

cd build/

echo "===========================================running make ======================================="

make -j16

./OPENGL_BEENCOOK
