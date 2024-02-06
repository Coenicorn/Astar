#!/usr/bin/bash

SCRIPTPATH=$(dirname "$0")

cd $SCRIPTPATH

bash ./make_staticlib.sh

rm -rf ./example/lib/libastar.a ./example/include/astar.h

cp ./lib_files/libastar.a ./example/lib
cp ./lib_files/astar.h ./example/include

echo "updated the binaries and headers in $SCRIPTPATH/example!"