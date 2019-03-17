#!/bin/bash

Date=`date "+%Y-%m-%d__%H:%M:%S"`
Front=`uname -a | awk '{printf("%s %s %s",$2,$13,$3)}'`
Uptime=`uptime | tr ':' ' ' | awk '{printf("up_%s_day,_%s_hours,_%s_minutes",$5,$7,$8)}'`

DiskInfo=`bash DiskLog.sh`
Diskall=`echo $DiskInfo | tail -2 | awk '{printf("%s", $4)}'`
Disk1=`echo $DiskInfo |tail -2| awk '{printf("%s", $6)}'`
a=${#Disk1}
Disk=`echo $Disk1 | cut -c -$[$a - 1]`
Dlevel=`echo nomal`
echo $Disk
if [[ $Disk -ge 80 ]];then
    Dlevel=`echo warning`
    if [[ $Disk -lt 90 ]];then
        Dlevel=`echo note`
    fi
fi

CpuInfo=`bash CpuLog.sh | tail -1`
CpuLoad=`echo $CpuInfo | tr ':' ' ' | awk '{printf("%s %s %s",$2,$3,$4)}'`
CpuSize=`cat /proc/meminfo | grep MemTotal`
CpuPct=`echo $CpuInfo | awk '{printf("%s", $5)}'`
CpuTem=`echo $CpuInfo | awk '{printf("%s", $6)}'`
Clevel=`echo nomal`
if [[ $CpuTem -ge 50 ]];then
    Clevel=`echo warning`
    if [[ $CpuTem -lt 90 ]];then
        Clevel=`echo note`
    fi
fi

MemInfo=`bash MemLog.sh`
Memsize=`echo $MemInfo | awk '{printf("%s", $2)}'`
Mem1=`echo $MemInfo | awk '{printf("%s",$4)}'`
Mlevel=`echo nomal`
if [[ `echo $Mem ">=70.00"` ]];then
    Mlevel=`echo warning`
    if [[ `echo $Mem "<80.00"` ]];then
        Mlevel=`echo note`
    fi
fi

echo $Date" "$Front" "$Uptime" "$CpuLoad" "$Diskall" "$Disk"% "$Memsize" "$Mem"% "$CpuTem"℃  "$Dlevel" "$Mlevel" "$Clevel
