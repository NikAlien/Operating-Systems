#!/bin/bash


for f in `cat who.txt | awk '{print $1}'`; do
	c=`cat ps.txt | grep -E -i -c "^$f "`
	echo "$f $c"
done

