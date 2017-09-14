FROM debian:latest

ARG LIBRSVG=librsvg-2.40.18

ARG DEBIAN_FRONTEND=noninteractive

RUN apt -y update && \
    apt -y install \
        build-essential \
        clang \
        curl \
        git \
        pkg-config \
        wget

RUN apt -y install \
    libcairo2-dev \
    libcroco3-dev \
    libgdk-pixbuf2.0-dev \
    libpango1.0-dev

WORKDIR /work

# Install radamsa
RUN git clone https://github.com/aoh/radamsa.git && \
    cd radamsa && make && make install

# Example svg files for fuzzing corpus
RUN mkdir -p /work/corpus /work/tests
RUN git clone --depth=1 https://github.com/openscad/svg-tests && \
    find svg-tests -name "*.svg" -exec cp {} /work/corpus \;

RUN wget -m -np \
        https://dev.w3.org/SVG/tools/svgweb/samples/svg-files/ \
        https://dev.w3.org/SVG/profiles/1.2T/test/svg/ \
    && \
    find dev.w3.org -name "*.svg" -exec cp {} /work/corpus \;

# Fetch and compile librsvg and install it under /app
RUN curl -fLO https://download.gnome.org/sources/librsvg/2.40/${LIBRSVG}.tar.xz
RUN xz -dc ${LIBRSVG}.tar.xz | tar xvf -
RUN ln -s /work/${LIBRSVG} /work/librsvg

WORKDIR /work/librsvg
RUN CC=clang \
    CFLAGS="-O2 -g -fsanitize=address -fno-omit-frame-pointer" \
    ./configure \
        --prefix=/app \
        --enable-introspection=no \
    && \
    make -j4 && \
    make install

WORKDIR /work
COPY fuzz.sh /work

# Generate test cases with something like:
# radamsa -n 10000 -o tests/fuzz-%n.%s corpus/*.svg
