#!/bin/sh
# asm56000 regression tests: run every command line in cases.txt through
# compare.py, which assembles with both the fixed-time original
# (re/bin_ft/ASM56000.EXE) and the rebuilt build/asm56000.exe and diffs
# exit status, stdout, stderr and every file written (.lst, .cld/.cln,
# error files, ...).  Until build/asm56000.exe exists every line fails
# with "orig ... new ..." (file not found) - that is expected; this
# script only has to run the cases correctly.
#
# usage: sh run_tests.sh   (run from tests/asm56000/)
cd "$(dirname "$0")"
ROOT=../..
ok=0
failed=0
while IFS= read -r line || [ -n "$line" ]; do
    case "$line" in
        ''|'#'*) continue ;;
    esac
    out=$(python "$ROOT/tests/compare.py" --time asm56000 $line 2>&1)
    if echo "$out" | grep -q '^OK '; then
        ok=$((ok + 1))
        echo "$out"
    else
        failed=$((failed + 1))
        echo "FAIL: asm56000 $line"
        echo "$out" | sed 's/^/    /'
    fi
done < cases.txt
echo "SUMMARY $ok 0 $failed"
