#!/bin/bash

MemUsedInfo=`free -h | awk "NR==2"|awk '{printf("%s",$3)}'`
a=${#MemUsedInfo}
a=$[$a - 1]
MemUsedInfoCal=`echo $MemUsedInfo| cut -c -$a`

MemAllInfo=`free -h | awk "NR==2"|awk '{printf("%s",$2)}'`
a=${#MemAllInfo}
a=$[$a - 1]
MemAllInfoCal=`echo $MemAllInfo| cut -c -$a`

MemEmptyInfo=`free -h | awk "NR==2"|awk '{printf("%s",$7)}'`
a=${#MemEmptyInfo}
a=$[$a - 1]
MemEmptyInfoCal=`echo $MemEmptyInfo| cut -c -$a`

MemPercent=`echo "scale=2; 100 * $MemUsedInfoCal / $MemAllInfoCal" | bc`

MemLstPct=`cat Memlog.txt | tail -1`
MemLstPct=`echo "scale=2; 0.3 * $MemLstPct + $MemPercent * 0.7" | bc`
echo $MemLstPct >> Memlog.txt

Date=`date "+%Y-%m-%d__%H:%M:%S"`

echo $Date"  "$MemAllInfo"  "$MemEmptyInfo"  "$MemPercent"%  "$MemLstPct"%"
