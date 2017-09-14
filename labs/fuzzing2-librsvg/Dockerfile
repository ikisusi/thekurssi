FROM debian:latest

ARG DEBIAN_FRONTEND=noninteractive

RUN echo 'deb-src http://deb.debian.org/debian stretch main' >>/etc/apt/sources.list
RUN echo 'deb-src http://deb.debian.org/debian stretch-updates main' >>/etc/apt/sources.list
RUN echo 'deb-src http://security.debian.org stretch/updates main' >>/etc/apt/sources.list

WORKDIR /work

RUN apt -y update && \
    apt -y install \
        clang \
        dpkg-dev \
        git \
        wget
RUN apt -y build-dep librsvg
RUN apt -y source librsvg || true

RUN git clone https://github.com/aoh/radamsa.git && \ 
    cd radamsa && \
    make && \
    make install

RUN ln -s /work/librsvg-2.40.16 /work/librsvg
WORKDIR /work/librsvg

RUN CC="clang" CFLAGS="-g -fsanitize=address -fno-omit-frame-pointer" \
    ./configure \
        --enable-introspection=no \
        --enable-static=yes && \
    make -j4

WORKDIR /work

# Example svg files for fuzzing corpus
RUN mkdir -p /work/corpus /work/tests
RUN git clone --depth=1 https://github.com/openscad/svg-tests && \
    find svg-tests -name "*.svg" -exec cp {} /work/corpus \;

COPY fuzz.sh /work

# Generate test cases with something like:
# radamsa -n 10000 -o tests/fuzz-%n.%s corpus/*.svg
