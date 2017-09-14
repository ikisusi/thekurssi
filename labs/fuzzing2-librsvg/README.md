# Fuzzing librsvg

This directory contains Dockerfile to help fuzzing librsvg. The built Docker
image is using Debian 9.1. 

Librsvg is built and instrumented with [Clang 3.8 AddressSanitizer](http://releases.llvm.org/3.8.0/tools/clang/docs/AddressSanitizer.html).

## Building

```sh
% docker build -t librsvg --rm .
```

## Running

```sh
docker run -ti librsvg ./fuzz.sh
```

## Fuzzing

### With Randamsa

Generate test material:

```sh
radamsa -n 10000 -o tests/fuzz-%n.%s corpus/*.svg
```

and run fuzzing:

```sh
sh fuzz.sh
```

...

### With AFL

...

### With libfuzzer

???
