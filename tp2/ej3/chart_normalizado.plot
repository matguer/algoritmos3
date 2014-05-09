set out "./chart_normalizado.png"
set xlabel "N (celdas por lado)"
set ylabel "Tiempo (clocks)"
set key left top
set terminal png size 1300,800 enhanced font "Helvetica,20"
plot "ejecuciones/ejecucion_normalizada.csv" title "Tiempos por N (celdas por lado)", x*x*x title "O(n^3)"

