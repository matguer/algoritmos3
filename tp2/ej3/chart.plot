#Terminal info
set terminal pngcairo enhanced font "courier,8" size 800,800 
set output 'ej_3_n_k_tiempos.png'

#Graph parameters
set dgrid3d 24,20
#set pm3d
set hidden3d
set samples 20, 20
set isosamples 21, 21
set contour base
set cntrparam levels auto 5
set style data lines
set grid layerdefault   linetype -1 linecolor rgb "gray"  linewidth 0.200,  linetype -1 linecolor rgb "gray"  linewidth 0.200
#set ztics 0.02

#Graph planes
#set view 60,30,1,1 #default
#set view 90,0,1,1 #XZ o Cant_CPUs X Metrica
#set view 90,90,1,1  #YZ o Quantum X Metrica

set key at screen 0.75,0.375

#Rangos
#set xrange [1:100]
#set yrange [1:100]

#Source datafile
#set datafile separator ","

#Multiplot
set multiplot layout 2,2 title "N - K - TIEMPOS" font ",14"

#XYZ
set xlabel "N (casillas por lado)" offset 0,-2
set ylabel "K (saltos extra)" offset 0,-2
set xtics 10 offset 0,-1
set ytics 10 offset 0,-1
set view 60,30,1,1
splot "ejecuciones/ejecucion_total.csv" title "n - k - tiempo", x*x*x*y title "c*n^3*y*22, c=22" 

#XZ o N x Tiempo
set xlabel "N (casillas por lado)" offset 0,-3
set xtics 10 offset 0,-2
unset ylabel
unset ytics
set view 90,0,1,1
splot "ejecuciones/ejecucion_total.csv" title "n - k - tiempo", x*x*x*y title "c*n^3*y*22, c=22" 

#YZ o K x Tiempo
set ylabel "K (saltos extra)" offset 0,-3
set ytics 10 offset 0,-2
unset xlabel
unset xtics
set view 90,90,1,1
splot "ejecuciones/ejecucion_total.csv" title "n - k - tiempo", x*x*x*y title "c*n^3*y*22, c=22" 

unset multiplot

