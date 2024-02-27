#!/bin/bash

c=0

for f in `find $1 -type file -name "*.c"`; do
	line=`cat $f | wc -l`
	if [ $line -gt 500 ]; then
		echo $f
		c=`expr $c + 1`
	fi
	if [ $c -eq 2 ]; then
		break
	fi
done
