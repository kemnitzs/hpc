#!/bin/bash

function make_run {

  BASE_DIR="$PWD"
  RUN_DIR=$BASE_DIR/run_dir_$1
  
  mkdir $RUN_DIR
  cd $RUN_DIR
  
  cp $BASE_DIR/my_program_src/* $RUN_DIR/
  ./my_program.sh
}

for (( i = 0; i < 10; i++ )); do
  make_run $i &
done
wait
