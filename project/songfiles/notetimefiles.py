#!/usr/bin/env python2.7
# notetimefiles.py
# This will run AUBIOPITCH on whatever mp3 you want

import sys
import os

libraryCommand="LD_LIBRARY_PATH=/usr/local/lib:./../aubio/aubio-0.4.5/build/src"

timesCommand="./aubiopitch ./" + sys.argv[1] + " | awk '{print $1}' > times.txt"

notesCommand="./aubiopitch ./" + sys.argv[1] + " | awk '{print $2}' > notes.txt"

os.system(libraryCommand)
os.system("export LD_LIBRARY_PATH")
os.system(timesCommand)
os.system(notesCommand)

