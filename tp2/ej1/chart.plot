set out "ej1_chart.png"
set xlabel "Cantidad de Cartas"
set ylabel "Tiempo (clocks)"
set key left top
set terminal png size 1300,800 enhanced font "Helvetica,20"
#plot "100tiempos.txt" title "Datos aleatorios seed 2", "300tiempos.txt" title "Datos aleatorios seed 3", x*x*x*100 title "O(n^3)"
#plot "300.csv" title "Datos aleatorios seed 3"
plot "100tiempos.txt" title "Datos aleatorios seed 2", "300tiempos.txt" title "Datos aleatorios seed 3", x*x*x*0.025 title "O(n^3)"
