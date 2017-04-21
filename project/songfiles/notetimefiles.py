#!/usr/bin/env python2.7
# notetimefiles.py
# This will run AUBIOPITCH on whatever mp3 you want

import sys
import os



timesCommand="aubiopitch ./" + sys.argv[1] + " | awk '{print $1}' > fourtime.txt"

notesCommand="aubiopitch ./" + sys.argv[1] + " | awk '{print $2}' > fournote.txt"



os.system(timesCommand)
os.system(notesCommand)

