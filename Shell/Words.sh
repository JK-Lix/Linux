#!/bin/basha

length=(0,0,0)
String=(,,)
File=(0,0,0)
dir=`find $1 -name "*" -type d`
for d in $dir; do
    var=0
    cd $d
    txt=`ls`
    for j in $txt; do
        judge_f=`file $j`
        for k in $judge_f; do
            if [[ $k = "text" ]]; then
                str=`cat $j |tr -c 'a-zA-Z0-9' ' '`
                for i in $str;  do
                    num=${#i}
                    temp=$[$var-1]
                    if [[ length[$(( $temp % 3 ))] -le $num ]]; then
                            if [[ ${string[0]} = $i ]]; then continue; fi
                            if [[ ${string[1]} = $i ]]; then continue; fi
                            if [[ ${string[2]} = $i ]]; then continue; fi
                        length[$(( $var % 3 ))]=$num
                        string[$(( $var % 3 ))]=$i
                        File[$(( $var % 3 ))]=$d/$j
                        var=$[$var+1]
                    fi
                done
                break
            fi
        done
    done
done
var=$[$var-1]
xb=$(( $var % 3 ))
echo 1-${string[$xb]}-${length[$xb]}-${File[$xb]}
var=$[$var-1]
xb=$(( $var % 3 ))
echo 2-${string[$xb]}-${length[$xb]}-${File[$xb]}
var=$[$var-1]
xb=$(( $var % 3 ))
echo 3-${string[$xb]}-${length[$xb]}-${File[$xb]}
