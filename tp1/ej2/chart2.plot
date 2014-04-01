set out "../informe/img/ej2_chart2.png"
set xlabel "Joyas encargadas"
set ylabel "Tiempo (clocks)"
set key left top
set terminal png size 1300,800 enhanced font "Helvetica,20"
plot "datachart2.out" title "Datos aleatorios seed 2", "datachart2bis.out" title "Datos aleatorios seed 3", 0.00001*x**2 title "O(n^2)"
