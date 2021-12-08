#!/bin/bash
make
./mollier > ./mollier.dat
gnuplot ./gnuplot/mollier.gp
