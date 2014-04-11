#!/bin/bash

# minima cantidad de casillas por lado
cant_filas=$1
# maxima cantidad de casillas por lado
cant_columnas=$2
# maxima cantidad de colores
cant_colores=$3
# path al fichero de salida
output_file=input_${cant_filas}x${cant_columnas}x${cant_colores}.data



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

# Se crea el header del archivo input
header="$cant_filas $cant_columnas $cant_colores"

# Se crean las fichas y se las guarda en un array
declare -a input=( "$header" "$(crearFichas $cant_filas $cant_columnas $cant_colores)" )

# se escriben los datos en el output
echo ${input[@]} > $output_file
