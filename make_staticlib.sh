#!/usr/bin/bash

SCRIPTPATH=$(dirname "$0")

cd $SCRIPTPATH

make clean
make all

ar -crs ./lib/libastar.a $(find ./obj -maxdepth 2 -name "*.o")

echo "libastar.a generated in $SCRIPTPATH/lib!"