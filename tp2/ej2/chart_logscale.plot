set out "../informe/img/ej2_chart_logscale.png"
set xlabel "Cantidad de pueblos (Total)"
set ylabel "Tiempo (clocks)"
set key left top
set terminal png size 1300,800 enhanced font "Helvetica,20"
#set xrange [0:1e+06]
#set yrange [0:1e+06]
set logscale y
plot "datachart1.out" title "Datos aleatorios (seed 1)", "datachart1bis.out" title "Datos aleatorios (seed 2)", x*x title "O(n^2))"

