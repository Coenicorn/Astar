#!/usr/bin/bash

# make sure you've run make first
cd ./obj
ar -crs libastar.a grid.o astar.o
cd ..
sudo rm -f ./lib_files/libastar.a
mv ./obj/libastar.a ./lib_files