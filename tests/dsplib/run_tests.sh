#!/bin/sh
# dsplib regression tests: run.py starts both tools with argv[0]="dsplib"
# (the tool prints its own name) and always uses the fixed clock
python run.py | grep -v "^all OK$"
