#!/bin/bash
#SBATCH -p batch 
#SBATCH -c 48
#SBATCH --time 01:00:00
time ./bin_probabilistic_pi 
