#!/bin/bash

result_gr=../greedy/ejecuciones_result_compare.csv
result_bl=./ejecuciones_result_compare.csv

n=`wc -l $result_bl | awk '{print $1}'`
cant_bl=0
cant_gr=0
cant_iguales=0

for i in `seq 1 $n`
do
	l_gr=$(sed -n ${i}p $result_gr)
	l_bl=$(sed -n ${i}p $result_bl)
	if [ "$l_bl" != "no" ] && [ "$l_gr" != "no" ]; then
		if [ "$l_bl" != "$l_gr" ]; then 
			w_bl=$(echo $l_bl | awk '{print $2}') 
			w_gr=$(echo $l_gr | awk '{print $2}') 
			if [ $w_bl -lt $w_gr ]; then 
				cant_bl=$((cant_bl + 1))
			elif [ $w_bl -gt $w_gr ]; then 
				cant_gr=$((cant_gr + 1))
			else
				cant_iguales=$((cant_iguales + 1))
			fi
		fi
	fi
done


echo -e "iguales\tmenor bl\tmenor greedy"
echo -e "${cant_iguales}\t\t${cant_bl}\t\t${cant_gr}"
