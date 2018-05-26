set xlabel "datasize"
set ylabel "time[s]"

set xrange[0:300000]

set key left
#set term png size 480,480
set term png enhanced size 1000,1000 font "Arial,20"

set output "mygraph.png"

plot [0:0.0 50000:0.0022 100000:0.0042 150000:0.0063 200000:0.0088 250000:0.0105 300000:0.0129],\
     [0:0.0 50000:0.0007 100000:0.0016 150000:0.0025 200000:0.0030 250000:0.0041 300000:0.0046]
