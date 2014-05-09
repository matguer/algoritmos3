#!/bin/bash

n=$1
k=$2

f_o=$(($RANDOM % n + 1))
c_o=$(($RANDOM % n + 1))

f_d=$(($RANDOM % n + 1))
c_d=$(($RANDOM % n + 1))

# GENERACION DE LA CABECERA DEL INPUT #

echo "$n $f_o $c_o $f_d $c_d $k"

# GENERACION DEL TABLERO #
for i in `seq 1 $n`; do
	
	declare -a saltos_fila=()

	for j in `seq 1 $n`; do
		salto=$(($RANDOM%(n-1) + 1))
		saltos_fila=( "${saltos_fila[@]}" "$salto" )
	done

	echo "${saltos_fila[@]}"
done
