#! /bin/bash

clear;

if cd build/;then
    echo "entering build ";
else mkdir build && cd build/
    echo "created directory build and entering "

fi


echo "================================================================================running cmake========================================================================="

if cmake ..; then
    make -j4 ;

    echo "================================================================================make=========================================================================" && make -j4 && ./OPENGL_BEENCOOK;

else exit 1;
fi
