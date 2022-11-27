#!/bin/bash

ITERATIONS=10
FILE1=$1
FILE2=$2

for i in `seq 1 ${ITERATIONS}`;
do
  { time ./test-syscall $FILE1 $FILE2; } 2>> syscall_$FILE1.res  
done


for j in `seq 1 ${ITERATIONS}`;
do
  { time ./test-stdes-buff $FILE1 $FILE2; } 2>> stdes_$FILE1.res
done