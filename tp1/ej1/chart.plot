set out "../informe/img/ej1_chart.png"
set xlabel "Cantidad de Camiones (Total)"
set ylabel "Tiempo (clocks)"
set key left top
set terminal png size 1300,800 enhanced font "Helvetica,20"
#set xrange [0:1e+06]
#set yrange [0:1e+06]
set logscale y
plot "datachart1.out" title "Datos aleatorios (seed 1)", "datachart1bis.out" title "Datos aleatorios (seed 2)", x*log(x)/log(2) title "O(n*log(n))"

