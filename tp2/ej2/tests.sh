#!/bin/bash


MIN_CANT_PUEBLOS=50000
MAX_CANT_PUEBLOS=100000
INTERVALO_PUEBLOS=1000

MIN_CANT_CENTRALES=1
MAX_CANT_CENTRALES=100000
INTERVALO_CENTRALES=4000

ejecutable=./ej2
generador_inputs=./generador_inputs.sh
output_file=ejecuciones/ejecucion_${MIN_CANT_PUEBLOS}_a_${MAX_CANT_PUEBLOS}_pueblos_${MIN_CANT_CENTRALES}_a_${MAX_CANT_CENTRALES}_centrales_`date +%Y%m%d_%H%M%S`.csv

# Se escribe el header del output
echo "pueblos, centrales, tiempo" > $output_file


for pueblos in `seq $MIN_CANT_PUEBLOS $INTERVALO_PUEBLOS $MAX_CANT_PUEBLOS`; do

	for centrales in `seq $MIN_CANT_CENTRALES $INTERVALO_CENTRALES $MAX_CANT_CENTRALES`;  do

		# Se genera el input para esta iteracion de centrales y pueblos
		input=$($generador_inputs $pueblos $centrales)

		# Se ejecuta el programa para el input generado en esta iteracion, se filtra
		# la salida para obtener la linea que imprime el tiempo y se guarda el valor
		tiempo=$( echo ${input} | $ejecutable 1 | grep "TIEMPO:" | awk '{ print $2 }' )

		# Se escriben los datos de esta iteracion en el output solo si no es cero
		test "$tiempo" != "0" && \
			echo "$pueblos, $centrales, $tiempo" >> $output_file

	done

done
