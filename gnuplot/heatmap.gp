unset key
set autoscale yfix
set autoscale xfix
set title "Heatmap" 
set cblabel "Temperature" 
set xlabel "Time" 
set ylabel "Thermal transfer" 
# http://gnuplot.sourceforge.net/docs_4.2/node216.html
#  7,5,15   ... traditional pm3d (black-blue-red-yellow)
#  3,11,6   ... green-red-violet
#  23,28,3  ... ocean (green-blue-white); try also all other permutations
#  21,22,23 ... hot (black-red-yellow-white)
#  30,31,32 ... color printable on gray (black-blue-violet-yellow-white)
#  33,13,10 ... rainbow (blue-green-yellow-red)
#  34,35,36 ... AFM hot (black-red-yellow-white)
set palette rgbformulae 33,13,10
NO_ANIMATION = 1
set pm3d map
set pm3d interpolate 10,10
splot 'heateq.dat' matrix with image
pause -1