#!/bin/bash
Test() {
    Net=$1
    for i in `seq 1 254`; do
        Ip=${Net}.${i}
        ping -c 1 -W 1 $Ip 2>&1 1>/dev/nullif 
        if [[ $? -eq 0 ]]; then
            echo $Ip
        fi
    done
}

for i in `seq 1 2`; do
    Test 192.168.$i
done
