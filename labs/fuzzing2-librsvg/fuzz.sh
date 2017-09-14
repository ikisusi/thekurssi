#!/bin/sh

# LeakSanitizer is spammy with librsvg
export ASAN_OPTIONS='detect_leaks=0'

for fuzzcase in tests/*.svg; do
    /app/bin/rsvg-convert -o /dev/null "${fuzzcase}"
    if [ $? -gt 1 ]; then
        echo "Test case was ${fuzzcase}"
        exit 1
    fi
done
