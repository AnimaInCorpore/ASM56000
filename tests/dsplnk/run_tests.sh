#!/bin/sh
# dsplnk regression tests: each line of cases.txt is a full DSPLNK argument
# list, run through compare.py against the original (fixed clock, since map
# files embed the assembly/link date). Prints one OK line per case, or the
# differences; exit status = number of failures.
# Run from tests/dsplnk after building build/dsplnk.exe:
#   sh run_tests.sh

C="python ../compare.py --time dsplnk"
fail=0
n=0
cat cases.txt cases_*.txt > cases_all.tmp 2>/dev/null
while IFS= read -r args || [ -n "$args" ]; do
    case "$args" in ''|'#'*) continue ;; esac
    n=$((n + 1))
    r=$(eval "$C $args" 2>&1)
    echo "$r" | head -40
    case "$r" in OK*) ;; *) fail=$((fail + 1)) ;; esac
done < cases_all.tmp
rm -f cases_all.tmp

echo "cases: $n  failures: $fail"
exit $fail
