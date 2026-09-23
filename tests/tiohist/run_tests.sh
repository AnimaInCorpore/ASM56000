#!/bin/sh
# tiohist regression tests
C="python ../compare.py"
$C tiohist trace.tio blocks.txt
$C tiohist trace.tio blocks2.txt
$C tiohist trace.tio empty.txt
$C tiohist empty.txt blocks.txt
$C tiohist trace.tio
$C tiohist nofile blocks.txt
