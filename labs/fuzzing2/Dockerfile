FROM ubuntu:latest

## updates and asan stuff

RUN apt-get update && apt-get upgrade -y && \
  apt-get install -y clang git make

## radamsa

RUN apt-get install -y wget
RUN git clone https://github.com/aoh/radamsa.git && cd radamsa && \
  make && make install

## target and the samples

WORKDIR /root/fuzzing2
COPY *.sample samples/
COPY fuzzing2.c build.sh fuzz.sh ./
RUN ./build.sh
