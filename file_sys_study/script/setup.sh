#!/bin/bash
bash ./script/cleanup.sh 
if [ ! -d "bin" ]; then
echo "build the executable output directory"
mkdir -p bin
echo "Done!"
fi

if [ ! -d "lib" ]; then 
echo "build the library output directory"
mkdir -p lib
echo "Done!"
fi

if [ ! -d "build" ]; then
echo "build the build directory"
mkdir -p build
echo "Done!"
fi

cd ./build
rm -rf ./*
cmake ..
make -j4
cd ..