#!/bin/bash


FZ=`cat /proc/loadavg | cut -c-14`
Temp=`cat /sys/class/thermal/thermal_zone0/temp`
WD=`echo "scale=2; $Temp / 1000" |bc`
CPUSAT1=`head -n 1 /proc/stat |awk -v sum1=0 -v IDLE1=0 '{for(i=2;i<=8;i++){sum1=sum1+$i}} END{printf("%d %d",sum1,IDLE1=$5)}'`
sleep 0.5
CPUSAT2=`head -n 1 /proc/stat |awk -v sum2=0 -v IDLE2=0 '{for(i=2;i<=8;i++){sum2=sum2+$i}} END{printf("%d %d",sum2,IDLE2=$5)}'`
IDLE1=0
IDLE2=0
COUNT=0
for i in $CPUSAT1; do
    if [[ $COUNT == 0 ]];then
        TOTAL1=$i
        COUNT=$[$COUNT + 1]
    fi
    IDLE1=$[0 - $IDLE1 - $i]
done
for i in $CPUSAT2; do
    if [[ $COUNT == 1 ]];then
        TOTAL2=$i
        COUNT=$[$COUNT + 1]
    fi
    IDLE2=$[0 - $IDLE2 - $i]
done
TOTAL=$[$TOTAL2-$TOTAL1]
pcpu=`echo "scale=2; 100 * ($IDLE2 - $IDLE1) / $TOTAL" | bc`
YN=`echo $WD '>=' 70 | bc`
STAT="Nomal"
if [[ $YN = 1 ]];then
    STAT="Warning"
fi
echo "Date:`date`"
echo "CPU:"$FZ" "$WD" "$pcpu"% "$STAT 
