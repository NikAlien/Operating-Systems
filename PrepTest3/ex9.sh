#!/bin/bash

find $1 type f | awk -F/ '{print $NF}' | sort | uniq -c

