#!/bin/bash

BIGFILE="/tmp/huge"

if [ ! -f $BIGFILE ]; then
    echo creating $BIGFILE
    for i in {1..1000} ; do cat /bin/bash >> $BIGFILE ; done
fi

echo compiling readfile.c
cc -std=c11 -Wall -Werror -o readfile readfile.c

for size in $(seq 200 200 5000) ; do	# 200 400 600 ... 5000
    ./readfile $BIGFILE $size
done
