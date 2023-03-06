#!/bin/bash
for DIR in $(ls -d */)
do
  cd $DIR
  echo "working in directory $DIR"
    for FILE in $(ls )
    do

      /home/piotrkali/projects/Algorithms-and-Optimization-Repository/Graph-Algorithms/Introduction/build/src/Introduction_run "$FILE"
    done
  cd ..
done