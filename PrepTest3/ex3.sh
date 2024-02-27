#!/bin/bash


for f in `find $1 -type f -name "*.log"`; do

	lines=`cat $f | sort`
	echo "$lines" > $f
done
