#!/bin/sh

MYFLAGS="-fsanitize=address -Weverything -Werror -O2 -g -fno-omit-frame-pointer"

clang ${MYFLAGS} -o fuzzing2 fuzzing2.c
