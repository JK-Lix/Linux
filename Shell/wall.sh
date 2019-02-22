#!/bin/bash

USER=`logname`
HOSTNAME=`hostname`
TTY=`who am i| awk '{print $2}'`
TIME=`date +"%a %b %d %T %Y"`
    
PreMessage="\nBroadcast message from $USER@$HOSTNAME ($TTY) ($TIME):"

Message=$1

for i in `w -h | awk '{print $2}'`;do
    echo -e "\n${PreMessage}\n" >> /dev/$i
    echo -e "$Message\n" >> /dev/$i
done
