#!/bin/bash

tests_inputs=/tmp/a
tests_outputs=./ejecuciones_result_compare.csv
ejecutable=./heuristica_grasp
input=""

test "$1" == "1" && rm -f $tests_outputs

cat $tests_inputs | \
while read line
do
	if [ "$line" == "SEP" ]; then
		echo -e "$input" | $ejecutable 7 2 >> $tests_outputs
		input=""
	else
		input=`echo -e "$input\n$line"`
	fi
done

sed -i 's/\ $//g' $tests_outputs
