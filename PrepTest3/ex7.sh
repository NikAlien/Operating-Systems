#!/bin/bash

line=""
c=0
for i in `cat $1`; do
	if [ $c -eq 1 ]; then
		line+=","
	fi
	line+=`echo $i | awk '{print $1"@scs.ubbcluj.ro"}'`
	c=1
 done
 echo $line
