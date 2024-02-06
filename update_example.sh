#!/usr/bin/env bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

bash $SCRIPT_DIR/make_staticlib.sh

rm -rf $SCRIPT_DIR/example/lib/libastar.a $SCRIPT_DIR/example/include/astar.h

cp $SCRIPT_DIR/lib/libastar.a $SCRIPT_DIR/example/lib
cp $SCRIPT_DIR/include/astar.h $SCRIPT_DIR/example/include

echo "updated the binaries and headers in $SCRIPT_DIR/example!"