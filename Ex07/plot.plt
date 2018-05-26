set xlabel "threads"
set ylabel "Speed improvement rate"

set xrange[0:56]

set key left
set term png enhanced size 1000, 1000 font "Arial, 20"

set output "mygraph.png"

plot "omp.txt" using 1:2 title "Speed improvement rate" w lp
