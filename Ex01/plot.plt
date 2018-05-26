set xlabel "datasize"
set ylabel "time[s]"

set xrange[0:900000]

set key left
#set term png size 640,480
set term png enhanced size 1000,1000 font "Arial,20"

set output "mygraph.png"

plot "output.txt" using 1:2 title "margesort" w lp
