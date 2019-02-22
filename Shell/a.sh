#!/bin/basha

declare -a arry
for i in `seq 2 5000`; do
    if [[ ${arry[$i]} -eq 0 ]]; then
        arry[0]=$[ ${arry[0]} + 1 ]
        arry[${arry[0]}]=$i
        let sum+=$i
        echo $sum
    fi
    for j in `seq 1 ${arry[0]}`; do
        if [[  $[ ${arry[$j]} * $i ] -gt 5000 ]]; then
            break
        fi
        arry[$[ ${arry[$j]} * $i ]]=1
        if [[ $[ $i % ${arry[$j]} ] -eq 0 ]]; then
            break
        fi
    done
done

