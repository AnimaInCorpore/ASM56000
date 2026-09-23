#!/bin/sh
# Run every tool's regression tests; prints a summary line per tool.
# usage: sh tests/run_all.sh   (after building into build/)
cd "$(dirname "$0")"
fail=0
for t in */run_tests.sh; do
    d=$(dirname "$t")
    out=$(cd "$d" && sh ./run_tests.sh 2>&1)
    n=$(echo "$out" | grep -c '^OK ')
    bad=$(echo "$out" | grep -vc -e '^OK ' -e '^$')
    printf '%-10s %3d OK' "$d" "$n"
    if [ "$bad" -ne 0 ]; then printf '  (%d lines of differences)\n' "$bad"; echo "$out" | grep -v '^OK '; fail=1; else echo; fi
done
exit $fail
