#!/bin/bash
make
./mollier > heateq.dat
gnuplot ./gnuplot/heatmap.gp