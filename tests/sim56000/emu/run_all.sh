#!/bin/sh
# Differential tests of the SIM56000 translation against the original executable running in the
# Unicorn emulator (pip install unicorn).  Needs re/bin/SIM56000.EXE (unzip assets/clas56-v6.3.0.zip).
cd "$(dirname "$0")" || exit 1
rc=0
for t in diff_*.py; do
    echo "== $t"
    python3 "$t" || rc=1
done
exit $rc
