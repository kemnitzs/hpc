#!/bin/bash
echo "running my_program"
time echo "scale=3000; 4*a(1)" | bc -l
echo "done running my_program"
