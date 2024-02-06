#!/usr/bin/bash

# make sure you've run make first
# cd ./obj
# ar -crs libastar.a grid.o astar.o
# cd ..
# sudo rm -f ./lib_files/libastar.a
# mv ./obj/libastar.a ./lib_files

SCRIPTPATH=$(dirname "$0")

cd $SCRIPTPATH

make clean
make all

ar -crs ./lib_files/libastar.a $(find ./obj -maxdepth 2 -name "*.o")

echo "libastar.a generated in $SCRIPTPATH/lib_files!"