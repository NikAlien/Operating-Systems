#!/bin/bash

cat df.txt | sed "s/M//g" | sed "s/%//g" | awk '$3 < 1000 || $5 > 80 {print $6}'



