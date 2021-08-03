#!/usr/bin/env bash

mkdir build
cd build

cmake ../

make

mv libs3d.a ../

cd ..

rm -r build

exit 0
