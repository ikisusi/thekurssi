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
docker run -ti --rm --network none librsvg ./fuzz.sh
```

## Fuzzing

### With Randamsa

Launch Docker image:

```sh
docker run -ti --rm --network none librsvg
```

and start fuzzing:

```sh
sh fuzz.sh
```

Observe found issues under `/work/crashes`:

```
ls -l /work/crashes/
-rw------- 1 root root 10461 Sep 15 16:57 065cad360861e6095efbc2002d33f7e2811751c7
-rw-r--r-- 1 root root  2957 Sep 15 16:57 065cad360861e6095efbc2002d33f7e2811751c7.txt
-rw------- 1 root root  5886 Sep 15 16:57 0672295f0a8dfc22bfd21da85c72050ab621076e
-rw-r--r-- 1 root root  2957 Sep 15 16:57 0672295f0a8dfc22bfd21da85c72050ab621076e.txt
...
```

...

### With AFL

...

### With libfuzzer

???
