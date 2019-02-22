#!/bin/bash
threHold=50
Time=`date +"%Y-%m-%d__%H:%M:%S"`
testNasty(){
    ps aux -q $1|awk -v time=$Time -v TH=$threHold 'NR==2{if($3 > TH || $4 > TH){printf("%s %s %s %s %s%% %s%%\n",time,$11,$2,$1,$3,$4)}else{printf"yes"}}'
}
eval $(ps aux|awk -v TH=$threHold '{if($3 > TH || $4 > TH){count++;printf("num[%d]=%s\n",count,$2)}}')
if [[ ${#num[*]} -eq 0 ]];then
    exit
fi
sleep 5
for i in ${num[*]};do
    ans=`testNasty $i`
    if [[ "$ans" != "yes"  ]];then
        echo $ans
    fi
done
