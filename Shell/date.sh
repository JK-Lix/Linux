#!/bin/bash

Y=$1
M=$2
D=$3

if [ $Y -lt 1 ] || [ $M -lt 1 ] || [ $D -lt 1 ]; then 
    echo "No"
    exit
else
    cal $M $Y|grep -q "$D" && echo Yes || echo No
fi
