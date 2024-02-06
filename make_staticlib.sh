#!/usr/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

make -C $SCRIPT_DIR clean
make -C $SCRIPT_DIR all

ar -crs $SCRIPT_DIR/lib/libastar.a $(find $SCRIPT_DIR/obj -maxdepth 2 -name "*.o")

echo "libastar.a generated in $SCRIPT_DIR/lib!"