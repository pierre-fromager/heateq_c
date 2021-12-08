reset
set autoscale fix
set palette defined (0 'white', 1 'green')
set tics scale 0
unset cbtics
set cblabel 'Score'
unset key
plot 'heateq.dat' matrix with image,\
     '' matrix using 1:2:(sprintf('%.2f', $3)) with labels font ',16'
