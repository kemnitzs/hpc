#!/bin/bash

RUN_ID=0
BASE_DIR=$PWD
RUN_DIR=$BASE_DIR/run_dir_$RUN_ID

mkdir $RUN_DIR
cd $RUN_DIR

cp $BASE_DIR/my_program_src/* $RUN_DIR/
cd $RUN_DIR

./my_program.sh
