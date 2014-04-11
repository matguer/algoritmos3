#!/bin/bash

# ########################################################################### #
# El presente script tiene como objetivo generar los inputs necesarios y la   #
# posterior ejecucion del programa con los mismos para obtener las            #
# estadisticas de los tiempos de ejecucion.				      #
# El script no recibe parametros de entrada ni escribe resultado alguno en el #
# stderr y/o stdout, aunque podria modificarse para que arroje los resultados #
# por el stdout y sean redireccionados externamente a un archivo.             #
# Aquellas ejecuciones que finalicen con tiempo 0 no seran tenidas en cuenta. #
# ########################################################################### #



# minima cantidad de casillas por lado
min_casillas_lado=4
# maxima cantidad de casillas por lado
max_casillas_lado=4
# maxima cantidad de colores
max_colores=8
# path del programa ejecutable
ejecutable=./ej3
# path al fichero de salida
output_file=ejecucion_${min_casillas_lado}_${max_casillas_lado}_${max_colores}.csv



# La funcion crearFichas debe crear y retornar un arreglo con las fichas
# para un tablero de $filas * $columnas. Las fichas deben tener valores entre
# 1 y $colores
# $1: cantidad de filas
# $2: cantidad de columnas
# $3: cantidad de colores
# return: array con las $filas * $columnas fichas con sus 4 colores
function crearFichas() {
	filas=$1
	columnas=$2
	colores=$3
	declare -a fichas=()

	# Se crean las $filas * $columnas fichas con sus 4 colores
	for (( i=0; i<($filas * $columnas * 4); i++ ))
	do
		color=$(( (RANDOM % colores) + 1 ))
		fichas=( ${fichas[@]} $color)
	done

	echo ${fichas[@]}
}


# ########################################################################### #
# ################################## MAIN ################################### #
# ########################################################################### #


# Se escribe la cabecera del output
echo "filas, columnas, colores, tiempo" > $output_file


# Para cada combinacion de filas * columnas genero el input
for filas in `seq $min_casillas_lado $max_casillas_lado`
do
	for columnas in `seq $min_casillas_lado $max_casillas_lado`
	do
		# Evito repeticiones de tableros, en nuestro caso nos importa la cantidad de fichas
		# por lo que un tablero de, por ejemplo, 3x5 es lo mismo que uno de 5x3.
		if [ $filas -ge $columnas ]
		then
			# Para todas las cantidades de colores entre 2 y $max_colores
			for cant_colores in `seq 2 $max_colores`
			do
				# Se crea el header del archivo input
				header="$filas $columnas $cant_colores"

				# Se crean las fichas y se las guarda en un array
				declare -a input=( "$header" "$(crearFichas $filas $columnas $cant_colores)" )

				# Se ejecuta el programa para el input generado en esta iteracion, se filtra
				# la salida para obtener la linea que imprime el tiempo y se guarda el valor
				tiempo=$( echo ${input[@]} | ./ej3 | grep "TIEMPO:" | awk '{ print $2 }' )

				# Se escriben los datos de esta iteracion en el output solo si no es cero
				test "$tiempo" != "0" && \
					echo "$filas, $columnas, $cant_colores, $tiempo" >> $output_file
			done
		fi
	done
done
