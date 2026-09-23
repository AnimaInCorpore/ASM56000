#!/bin/sh
# strip regression tests: run from this directory after building build/strip.exe
C="python ../compare.py"
T='^s[0-9a-z]+\.?$'
$C strip t1.cld
$C strip -q t1.cld t2.cld
$C strip -Q t2.cld
$C --ignore "$T" strip t2.cln
$C strip
$C strip -x t1.cld
$C strip nofile
$C --stdin t1.cld strip -
$C --stdin t2.cld strip -q -
