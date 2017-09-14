FROM ubuntu:latest

# Environment variables used by the fuzzer

RUN apt-get update && apt-get upgrade -y && apt-get install -y clang

WORKDIR /root/fuzzing2
COPY *.sample samples/
COPY fuzzing2.c build.sh ./
RUN ./build.sh
