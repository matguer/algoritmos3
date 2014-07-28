#!/bin/bash

tests_inputs=../inputs/instacias_grasp.csv
tests_outputs=./ejecuciones_result.csv
tests_times=./ejecuciones_time.csv
ejecutable=./heuristica_grasp
input=""

test "$1" == "1" && rm -f $tests_outputs $tests_times

cat $tests_inputs | \
while read line
do
	if [ "$line" == "SEP" ]; then
		echo -e "$input" | $ejecutable 7 2 2>> $tests_times 1>> $tests_outputs
		input=""
	else
		input=`echo -e "$input\n$line"`
	fi
done

sed -i 's/\ $//g' $tests_outputs
