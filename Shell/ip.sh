#!/bin/bash
worker(){
for i in 1 2 3 ;do
       ping -c 1 ${1}.$(($2+$i))
done
}

for j in {0..254} ;do
        if [[ $j%3 -eq "1" ]] ;then
                worker 192.168.1 $j
        fi
        if [[ $j%3 -eq "2" ]] ;then
                worker 192.168.2 $j
        fi
done
