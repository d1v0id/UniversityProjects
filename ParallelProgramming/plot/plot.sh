#!/bin/bash
echo "set term png; set output \"plot.png\"; set grid; set xlabel \"Время, ms\"; set ylabel \"Ядра, шт\"; plot \"plot.dat\" with lines" | gnuplot
