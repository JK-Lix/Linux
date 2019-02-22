#!/bin/bash

AllSize=(0, 0)
AvSize=(0, 0)
Date=`date "+%Y-%m-%d__%H:%M:%S"`

DiskInfo=`df -l | awk "NR==2"`
count=0
line=2
sumAl=0
sumAv=0
while [ -n "$DiskInfo" ];do
    judge=`echo $DiskInfo | cut -c -1`
    if [[ $judge = / ]];then
        UsePct=`echo $DiskInfo | tr ' ' '\n'| awk "NR==5"`
        All=`echo $DiskInfo | tr ' ' '\n' | awk "NR==2"`
        sumAl=$[$sumAl + $All]
        Available=`echo $DiskInfo | tr ' ' '\n'| awk "NR==4"`
        sumAv=$[$sumAv + $Available]
        Disk=`echo $DiskInfo | tr ' ' '\n' | awk "NR==6"`
        echo $Date" 1 "$Disk" "$All" "$Available" "$UsePct
    fi
    line=$[$line + 1]
    DiskInfo=`df -l | awk "NR==$line"`
done
DiskUsePct=`echo "scale=0; 100 * ($sumAl - $sumAv) / $sumAl" | bc`
echo $Date" 0 disk "$sumAl" "$sumAv" "$DiskUsePct"%"
