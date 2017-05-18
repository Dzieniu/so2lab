#!/bin/sh

if [ $# -lt 2 ]; then               # check argv length
    echo "Usage: $0 LINKA LINKB"    # print usage info
    exit 1                          # exit
fi


# osx 'readlink' is different, missing -f option, use 'greadlink' form gnu
if [ `greadlink -f $1` == `greadlink -f $2` ]; then
    echo "TAK";
else
    echo "NIE";
fi;
