#!/bin/sh
# srec regression tests: run_tests.py runs every case through cmpname.py
# (both tools started as SREC.EXE, since srec prints its argv[0])
python run_tests.py | sed -n 's/^\([0-9]*\) OK, \([0-9]*\) known differences*, \([0-9]*\) failed$/SUMMARY \1 \2 \3/p; /^known difference/p; /FAIL\|differs/p'
