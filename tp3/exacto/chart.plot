set out "../informe/img/exacto_chart.png"
set xlabel "Cantidad de aristas"
set ylabel "Tiempo (clocks)"
set key left top
set terminal png size 1300,800 enhanced font "Helvetica,20"
#set xrange [0:1e+06]
#set yrange [0:1e+06]
#set logscale y
#fac(x) = (int(x)==0) ? 1.0 : int(x) * fac(int(x)-1.0)
plot "../informe/datos/datos_exacto.csv" title "Tiempos por cantidad de aritas"

