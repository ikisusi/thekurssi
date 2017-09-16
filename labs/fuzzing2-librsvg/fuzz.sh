#!/bin/sh

# LeakSanitizer is spammy with librsvg
export ASAN_OPTIONS='detect_leaks=0:exitcode=127'

mkdir -p /work/crashes /work/tests
while true; do
    echo "Generating test cases"
    radamsa -n 1000 -o tests/fuzz-%n.%s corpus/*.svg

    for fuzzcase in tests/*.svg; do
        /app/bin/rsvg-convert -o /dev/null "${fuzzcase}"
        if [ $? -eq 127 ]; then
            echo "Test case was ${fuzzcase}"
            SHA=$(sha1sum "${fuzzcase}" | cut -d' ' -f1)
            cp "${fuzzcase}" "crashes/${SHA}"
            /app/bin/rsvg-convert -o /dev/null "${fuzzcase}" 2>&1 | tee "crashes/${SHA}.txt"
        fi
    done

    echo "Cleaning up"
    rm -rf /work/tests/*
done
