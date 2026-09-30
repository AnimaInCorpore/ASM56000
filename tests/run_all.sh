#!/bin/sh
# Run every tool's regression tests; prints a summary line per tool.
# usage: sh tests/run_all.sh   (after building into build/)
# A run_tests.sh prints one "OK ..." line per passing case, or a single
# "SUMMARY <ok> <known> <failed>" line; "known difference" lines are
# documented, accepted differences; anything else is a failure.
cd "$(dirname "$0")"
fail=0
for t in */run_tests.sh; do
    d=$(dirname "$t")
    if [ ! -e "../build/$d.exe" ] && [ ! -e "../build/$d" ]; then
        printf '%-10s SKIP (build/%s.exe not built yet)\n' "$d" "$d"
        continue
    fi
    out=$(cd "$d" && sh ./run_tests.sh 2>&1)
    n=$(echo "$out" | grep -c '^OK ')
    k=$(echo "$out" | grep -c '^known difference')
    s=$(echo "$out" | sed -n 's/^SUMMARY \([0-9]*\) \([0-9]*\) \([0-9]*\)$/\1 \2 \3/p')
    bad=$(echo "$out" | grep -v -e '^OK ' -e '^$' -e '^known difference' -e '^SUMMARY ' -e '^failures: 0$' | grep -c .)
    if [ -n "$s" ]; then
        set -- $s
        n=$1; k=$2
        [ "$3" -ne 0 ] && bad=$((bad + $3))
    fi
    printf '%-10s %4d OK' "$d" "$n"
    [ "$k" -ne 0 ] && printf ', %d known differences' "$k"
    if [ "$bad" -ne 0 ]; then printf '  (%d failures)\n' "$bad"; echo "$out" | grep -v -e '^OK ' -e '^known difference' -e '^SUMMARY ' -e '^failures: 0$'; fail=1; else echo; fi
done
exit $fail
