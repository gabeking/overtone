# notetimefiles.py
# This will run AUBIOPITCH on whatever mp3 you want

import sys
import os

timesCommand = "aubiopitch ./" + sys.argv[1] + " | awk '{print $1}' > times.txt"
notesCommand = "aubiopitch ./" + sys.argv[1] + " | awk '{print $2}' > notes.txt"

os.system(timesCommand)
os.system(notesCommand)

