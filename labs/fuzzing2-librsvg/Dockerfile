FROM debian:latest

RUN echo 'deb-src http://deb.debian.org/debian stretch main' >>/etc/apt/sources.list
RUN echo 'deb-src http://deb.debian.org/debian stretch-updates main' >>/etc/apt/sources.list
RUN echo 'deb-src http://security.debian.org stretch/updates main' >>/etc/apt/sources.list

WORKDIR /work

RUN apt -y update && \
    apt -y install \
        clang \
        dpkg-dev \
    && \
    apt build-dep librsvg && \
    apt source librsvg || true

WORKDIR /work/librsvg-2.40.16

RUN CC="clang" CFLAGS="-fsanitize=address -fno-omit-frame-pointer" \
    ./configure \
        --enable-introspection=no \
        --enable-static
