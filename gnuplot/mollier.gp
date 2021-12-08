#!/usr/bin/gnuplot

set grid
set title 'Mollier'
set xlabel 'Temperature'
set ylabel 'Hygrométrie %'

# @url https://colordesigner.io/gradient-generator
set style line 9 lc rgb '#6e72fa' lt 1 lw 1 pi -1 ps 1.0
set style line 8 lc rgb '#9564ea' lt 9 lw 1 pi -1 ps 1.0
set style line 7 lc rgb '#b055d8' lt 6 lw 1 pi -1 ps 1.0
set style line 6 lc rgb '#c545c3' lt 7 lw 1 pi -1 ps 1.0
set style line 5 lc rgb '#d433ac' lt 8 lw 1 pi -1 ps 1.0
set style line 4 lc rgb '#dd2094' lt 1 lw 1 pi -1 ps 1.0
set style line 3 lc rgb '#e20d7c' lt 9 lw 1 pi -1 ps 1.0
set style line 2 lc rgb '#e30464' lt 6 lw 1 pi -1 ps 1.0
set style line 1 lc rgb '#df114d' lt 7 lw 1 pi -1 ps 1.0

set xrange [-130:130]

plot './mollier.dat' \
    index 0 using 2:3 ls 9 with lines title col(1), \
    '' index 1 using 2:3 ls 8 with lines title col(1), \
    '' index 2 using 2:3 ls 7 with lines title col(1), \
    '' index 3 using 2:3 ls 6 with lines title col(1), \
    '' index 4 using 2:3 ls 5 with lines title col(1), \
    '' index 5 using 2:3 ls 4 with lines title col(1), \
    '' index 7 using 2:3 ls 3 with lines title col(1), \
    '' index 8 using 2:3 ls 2 with lines title col(1), \
    '' index 9 using 2:3 ls 1 with lines title col(1)

pause -1