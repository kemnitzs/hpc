#!/bin/bash

RUN_ID=0
CURRENT_DIR=$PWD
RUN_DIR=$CURRENT_DIR/run_dir_$RUN_ID

mkdir $RUN_DIR
cd $RUN_DIR

cp $CURRENT_DIR/my_program_src/* $RUN_DIR/
cd $RUN_DIR

./my_program.sh
