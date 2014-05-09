#!/bin/bash

min_n=25
max_n=100
intervalo_n=1

generador_input=./generador_inputs.sh
ejecutable=./ej3

output_file=ejecuciones/ejecucion_${min_n}_a_${max_n}_`date +%Y%m%d_%H%M%S`.csv

# Se escribe el header del output
echo -e "n\tk\ttiempo" > $output_file

for n in `seq $min_n $intervalo_n $max_n`; do
	
	for k in `seq 0 $n`; do
		
		# Se genera el input para esta iteracion de n
		input=$($generador_input $n $k)


		# Se ejecuta el programa para el input generado en esta iteracion, se filtra
		# la salida para obtener la linea que imprime el tiempo y se guarda el valor
		tiempo=$( echo ${input} | $ejecutable 1 | grep "TIEMPO:" | awk '{ print $2 }' )

		# Se escriben los datos de esta iteracion en el output solo si no es cero
		test "$tiempo" != "0" && \
			echo -e "$n\t$k\t$tiempo" >> $output_file
	done

done
