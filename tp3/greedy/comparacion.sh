#!/bin/bash

result_exacto=../exacto/ejecuciones_result.csv
result_heu=./ejecuciones_result_compare.csv

n=`wc -l $result_exacto | awk '{print $1}'`
cant_iguales=0
cant_sin_sol=0
cant_sin_sol_iguales=0

for i in `seq 1 $n`
do
	l_exacto=$(sed -n ${i}p $result_exacto)
	l_heu=$(sed -n ${i}p $result_heu)
	if [ "$l_exacto" == "no" ]; then
		cant_sin_sol=$((cant_sin_sol + 1))
	elif [ "$l_exacto" == "$l_heu" ]; then 
		cant_iguales=$((cant_iguales + 1)) 
	fi
	if [ "$l_exacto" == "no" ] && [ "$l_heu" == "no" ]; then
		cant_sin_sol_iguales=$((cant_sin_sol_iguales + 1))
	fi
done

cant_con_sol=$((n - cant_sin_sol))
cant_distintos=$((cant_con_sol - cant_iguales))

echo -e "corridas\tsin solucion\tcon solucion\tiguales\tdistintos\tsin solucion iguales"
echo -e "${n}\t\t${cant_sin_sol}\t\t${cant_con_sol}\t\t${cant_iguales}\t${cant_distintos}\t${cant_sin_sol_iguales}"
