#!/bin/bash
module load clang/7.0
scan-build cmake .
scan-build make 
