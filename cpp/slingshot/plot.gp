set terminal png
set output 'course.png'
set size ratio -1
plot 'plot.in' with lines, 'planets.gp' using 1:2:3 with circles
