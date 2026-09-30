#!/bin/sh
# SIM56000 scripted sessions: rebuilt tool vs. golden transcripts made from the original.
# (Regenerate goldens on Windows with: python tests/sim56000/simtest.py gold)
python "$(dirname "$0")/simtest.py" check
