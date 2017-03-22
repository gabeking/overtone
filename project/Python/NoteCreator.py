# NotePlayer.py
# This python program will take a song and make it into 
# a ADT that will contain the notes. 					
# Author: Matthew D'Alonzo

import pyaudio
import math
import struct
import random


def play_tone(frequency, amplitude, duration, fs, stream):
    N = int(fs / frequency)
    T = int(frequency * duration)  # repeat for T cycles
    dt = 1.0 / fs
    # 1 cycle
    tone = (amplitude * math.sin(2 * math.pi * frequency * n * dt)
            for n in xrange(N))
    # todo: get the format from the stream; this assumes Float32
    data = ''.join(struct.pack('f', samp) for samp in tone)
    for n in xrange(T):
        stream.write(data)

fs = 48000
p = pyaudio.PyAudio()
stream = p.open(
    format=pyaudio.paFloat32,
    channels=1,
    rate=fs,
    output=True)

# play the C major scale
notes = []
graphedNotes = []
times = []
f = open('notes.txt', "r")
hertz = f.readlines()

g = open('times.txt', "r")
lines = g.readlines()

for i in hertz:
	if float(i.rstrip()) > 0:
		notes.append(float(i.rstrip()))
	else:
		notes.append(1.000)

for i in notes:
	if i <= 16.35:
		graphedNotes.append(16.35)
	elif i <= 17.32:
		graphedNotes.append(17.32)
	elif i <= 18.35:
		graphedNotes.append(18.35)
	elif i <= 19.45:
		graphedNotes.append(19.45)
	elif i <= 20.60:
		graphedNotes.append(20.60)
	elif i <= 21.83:
		graphedNotes.append(21.83)
	elif i <= 23.12:
		graphedNotes.append(23.12)
	elif i <= 24.50:
		graphedNotes.append(24.50)
	elif i <= 25.96:
		graphedNotes.append(25.96)
	elif i <= 27.50:
		graphedNotes.append(27.50)
	elif i <= 29.14:
		graphedNotes.append(29.14)
	elif i <= 30.87:
		graphedNotes.append(30.87)
	elif i <= 32.70:
		graphedNotes.append(32.70)
	elif i <= 34.65:
		graphedNotes.append(34.65)
	elif i <= 36.71:
		graphedNotes.append(36.71)
	elif i <= 38.89:
		graphedNotes.append(38.89)
	elif i <= 41.20:
		graphedNotes.append(41.20)
	elif i <= 43.65:
		graphedNotes.append(43.65)
	elif i <= 46.25:
		graphedNotes.append(46.25)
	elif i <= 49.00:
		graphedNotes.append(49.00)
	elif i <= 51.91:
		graphedNotes.append(51.91)
	elif i <= 55.00:
		graphedNotes.append(55.00)
	elif i <= 58.27:
		graphedNotes.append(58.27)
	elif i <= 61.74:
		graphedNotes.append(61.74)
	elif i <= 65.41:
		graphedNotes.append(65.41)
	elif i <= 69.30:
		graphedNotes.append(69.30)
	elif i <= 73.42:
		graphedNotes.append(73.42)
	elif i <= 77.78:
		graphedNotes.append(77.78)
	elif i <= 82.41:
		graphedNotes.append(82.41)
	elif i <= 87.31:
		graphedNotes.append(87.31)
	elif i <= 92.50:
		graphedNotes.append(92.50)
	elif i <= 98.00:
		graphedNotes.append(98.00)
	elif i <= 103.83:
		graphedNotes.append(103.83)
	elif i <= 110.00:
		graphedNotes.append(110.00)
	elif i <= 116.54:
		graphedNotes.append(116.54)
	elif i <= 123.47:
		graphedNotes.append(123.47)
	elif i <= 130.81:
		graphedNotes.append(130.81)
	elif i <= 138.59:
		graphedNotes.append(138.59)
	elif i <= 146.83:
		graphedNotes.append(146.83)
	elif i <= 155.56:
		graphedNotes.append(155.56)
	elif i <= 164.81:
		graphedNotes.append(164.81)
	elif i <= 174.61:
		graphedNotes.append(174.61)
	elif i <= 185.00:
		graphedNotes.append(185.00)
	elif i <= 196.00:
		graphedNotes.append(196.00)
	elif i <= 207.65:
		graphedNotes.append(207.65)
	elif i <= 220.00:
		graphedNotes.append(220.00)
	elif i <= 233.08:
		graphedNotes.append(233.08)
	elif i <= 246.94:
		graphedNotes.append(246.94)
	elif i <= 261.63:
		graphedNotes.append(261.63)
	elif i <= 277.18:
		graphedNotes.append(277.18)
	elif i <= 293.66:
		graphedNotes.append(293.66)
	elif i <= 311.13:
		graphedNotes.append(311.13)
	elif i <= 329.63:
		graphedNotes.append(329.63)
	elif i <= 349.23:
		graphedNotes.append(349.23)
	elif i <= 369.99:
		graphedNotes.append(369.99)
	elif i <= 392.00:
		graphedNotes.append(392.00)
	elif i <= 415.30:
		graphedNotes.append(415.30)
	elif i <= 440.00:
		graphedNotes.append(440.00)
	elif i <= 466.16:
		graphedNotes.append(466.16)
	elif i <= 493.88:
		graphedNotes.append(493.88)
	elif i <= 523.25:
		graphedNotes.append(523.25)
	elif i <= 554.37:
		graphedNotes.append(554.37)
	elif i <= 587.33:
		graphedNotes.append(587.33)
	elif i <= 622.26:
		graphedNotes.append(622.26)
	elif i <= 659.25:
		graphedNotes.append(659.25)
	elif i <= 698.46:
		graphedNotes.append(698.46)
	elif i <= 739.99:
		graphedNotes.append(739.99)
	elif i <= 783.99:
		graphedNotes.append(784.99)
	elif i <= 830.61:
		graphedNotes.append(830.61)
	elif i <= 880.00:
		graphedNotes.append(880.00)
	elif i <= 932.33:
		graphedNotes.append(932.33)
	elif i <= 987.77:
		graphedNotes.append(987.77)
	elif i <= 1046.50:
		graphedNotes.append(1046.50)
	elif i <= 1108.73:
		graphedNotes.append(1108.73)
	elif i <= 1174.66:
		graphedNotes.append(1174.66)
	elif i <= 1244.51:
		graphedNotes.append(1244.51)
	elif i <= 1318.51:
		graphedNotes.append(1318.51)
	elif i <= 1396.91:
		graphedNotes.append(1396.91)
	elif i <= 1479.98:
		graphedNotes.append(1479.98)
	elif i <= 1567.98:
		graphedNotes.append(1567.98)
	elif i <= 1661.22:
		graphedNotes.append(1661.22)
	elif i <= 1760.00:
		graphedNotes.append(1760.00)
	elif i <= 1864.66:
		graphedNotes.append(1864.66)
	else:
		graphedNotes.append(1.000)

rectifiedNotes = []

for i in graphedNotes:
	if i > 0 and i <=110:
		rectifiedNotes.append(i*4)
	elif i > 110 and i < 220:
		rectifiedNotes.append(i*2)
	elif i < 880 and i <= 1320:
		rectifiedNotes.append(i)
	elif i > 1320 and i <=1740:
		rectifiedNotes.append(i/2)
	elif i>1740:
		rectifiedNotes.append(i/5)
	else:
		rectifiedNotes.append(i)

smoothedNotes = []
smoothingVal = 4
for index, val in enumerate(rectifiedNotes):
	if index % smoothingVal == 0:
		smoothedNotes.append(val)

for index, j in enumerate(lines):
	if index+1 < len(lines):
		if float(lines[index+1].rstrip())-float(lines[index]) > 0:
			times.append((float(lines[index+1].rstrip())-float(lines[index])))
		else:
			times.append(0)
	else:
		times.append(0)

for i, tone in enumerate(notes):
	print tone
	play_tone(tone, 0.5, times[i], fs, stream)



stream.close()
p.terminate()
