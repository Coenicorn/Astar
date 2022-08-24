#!/usr/bin/bash

# make sure you've run make first
sudo rm -rf ./bin/*
cp ./src/grid.o ./bin/
cp ./src/astar.o ./bin/
cd ./bin
ar -crs libastar.a grid.o astar.o
cd ..
sudo rm -f ./lib_files/libastar.a
mv ./bin/libastar.a ./lib_files
make clean