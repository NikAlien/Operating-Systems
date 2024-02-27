#!/bin/bash

lines=`find $1 -type f`
files=`ls -l $lines | grep "^........w" | awk '{print $9" "}'`

for f in $files; do
	echo `ls -l $f | awk '{print $1" "$9}'`
	chmod o-w $f
	echo `ls -l $f | awk '{print $1" "$9}'`
done
