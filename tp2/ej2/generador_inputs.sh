#!/bin/bash

# El script debe recibir la cantidad de pueblos y centrales para generar el input.
# Se chequea que se reciban dos parametros.
if [ $# -ne 2 ]; then 
	echo "Error en la cantidad de inputs" 
	exit 1
fi

# Maximo valor que puede tomar la coordenada X
MAX_COORD_X=1000
# Maximo valor que puede tomar la coordenada Y
MAX_COORD_Y=1000

# Se setea la cantidad de pueblos y centrales con los parametros recibidos
cant_pueblos=$1
cant_centrales=$2

# Se escribe el header del input con la cantidad de pueblos y centrales
echo "$cant_pueblos $cant_centrales"

# Se generan las coordenadas de los pueblos aleatoriamente
for i in `seq $cant_pueblos`; do
	x=$(( RANDOM % $MAX_COORD_X ))
	y=$(( RANDOM % $MAX_COORD_Y ))
	echo "${x} ${y}"
done

exit 0
