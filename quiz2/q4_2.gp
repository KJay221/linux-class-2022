reset
set title 'performance comparison'
set xlabel 'bitmap density'
set ylabel 'time(sec)'
set term png font 'Times_New_Roman,12'
set output 'runtime.png'
set xtics 1 ,8 ,64
set key left

plot \
"q4_2.txt" using 1:2 with linespoints linewidth 2 title 'naive', \
"q4_2.txt" using 1:3 with linespoints linewidth 2 title 'improve',