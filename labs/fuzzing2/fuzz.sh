#!/bin/sh

mkdir -p tests
radamsa -n 100 -o tests/fuzz-%n.%s samples/*.sample

#ASAN_OPTIONS="verbosity=1"

for i in samples/*.sample tests/*.sample; do
  echo "Running with: $i"
  ./fuzzing2 ${i} && echo "OK"
done
