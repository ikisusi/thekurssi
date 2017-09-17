# Fuzzing librsvg

This directory contains Dockerfile to help fuzzing librsvg. The built Docker
image is using `debian:latest`, which at the time of our testing was Debian 9.1.

## Instrumentation

Librsvg is built and instrumented with [Clang 3.8 AddressSanitizer](http://releases.llvm.org/3.8.0/tools/clang/docs/AddressSanitizer.html).

Due to excessive memory leaks in the librsvg build and tooling we disabled
`leaksanitizer` [`detect_leaks=0`] and to simplify scaffolding for the fuzzing we
changed the ASAN exit code to be 127 [`exitcode=127`].

## Fuzzer

We chose [Radamsa](https://github.com/aoh/radamsa) to be the fuzzer of choice
for this exercise and added it be installed in our [Dockerfile](Dockerfile).

## Sample based fuzzing and the corpus

Since Radamsa is a sample based fuzzer then fuzzing is as good as the initial
samples are. As part of the build we fetch samples from <https://github.com/openscad/svg-tests>,
<https://dev.w3.org/SVG/tools/svgweb/samples/svg-files/> and
<https://dev.w3.org/SVG/profiles/1.2T/test/svg/> as our fuzzing corpus.

## Scaffolding

To make the fuzzing with Radamsa as automatic as possible we have
made a [`fuzz.sh` script](fuzz.sh) that generates batches of test cases
and executes them while monitoring for failures.

## Building the Docker image

```sh
% docker build -t librsvg --rm .
```

## Fuzzing

Launch Docker image, in order to protect the innocent you can disable network
while fuzzing:

```sh
docker run -ti --rm --network none librsvg
```

and start fuzzing:

```sh
sh fuzz.sh
```

Observe found issues under `/work/crashes`:

```sh
ls -l /work/crashes/
-rw------- 1 root root 10461 Sep 15 16:57 065cad360861e6095efbc2002d33f7e2811751c7
-rw-r--r-- 1 root root  2957 Sep 15 16:57 065cad360861e6095efbc2002d33f7e2811751c7.txt
-rw------- 1 root root  5886 Sep 15 16:57 0672295f0a8dfc22bfd21da85c72050ab621076e
-rw-r--r-- 1 root root  2957 Sep 15 16:57 0672295f0a8dfc22bfd21da85c72050ab621076e.txt
...
```

And remember to copy the crashes out from Docker image for further analysis:

```sh
docker cp <container id>:/work/crashes/ .  # <- mind the dot
```

## Reproduction environment

To test if found issues can be reproduced we made
another [Dockerfile](Dockerfile.repro) to have clean Debian
environment with default packages and debug symbols.

Build the repro image:

```sh
docker build -t librsvg-repro -f Dockerfile.repro .
```

To run the reproduction image Seccomp needs to be disabled so that GDB
can disable ASLR when debugging (ref. [StackOverflow](https://stackoverflow.com/questions/35860527/warning-error-disabling-address-space-randomization-operation-not-permitted#comment62818827_35860527)).

```sh
docker run -ti --rm --security-opt seccomp=unconfined librsvg-repro
```

## Additional fuzzers to try out

In addition to fuzzing Radamsa you could try out [AFL](http://lcamtuf.coredump.cx/afl/)
or [libFuzzer](https://llvm.org/docs/LibFuzzer.html).

## Results

We did a bit of overnight, or actually 24h, fuzzing on a laptop and ended
up reporting the following issues:

* [Bug 787796 - Fuzz: Crash with circle with large numerical "r" attribute](https://bugzilla.gnome.org/show_bug.cgi?id=787796)
* [Bug 787799 - Fuzz: Crash with large numerical value in stroke-width attribute](https://bugzilla.gnome.org/show_bug.cgi?id=787799)
