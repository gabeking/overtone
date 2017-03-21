/* note.cpp
 * implementation for note object for CSE20312 project
 * Jeff Klouda
 */

// NOTES
// Consider using a pre-calculated table to obtain frequencies, much more
// efficient than calculating on a note by note basis

#include "note.h"
#include <cmath>

using namespace std;

//constructor
note::note(char letter, int octave, int length, bool sharp, bool flat, 
float tempo) {
    this->letter = letter;
    this->octave = octave;
    this->length = length;
    this->sharp = sharp;
    this->flat = flat;
    this->calcFreq();
    this->calcTime(tempo); 
}

note::~note() {}; // destructor
// ***consider looking up precalculated values from table
void note::calcFreq() { 
    float f0 = 440; // fixed freq of A4
    int n = (octave - 4) * 12 + sharp - flat; // number of half steps from A4
    switch(letter) {
        case 'b' : n += 2; break;
        case 'c' : n -= 9; break;
        case 'd' : n -= 7; break;
        case 'e' : n -= 5; break;
        case 'f' : n -= 4; break;
        case 'g' : n -= 2; break;
    }
    float tw = 1.0/12.0;
    float a = pow(2, tw); // twelth root of 2 (used in freq equation)
    freq = f0 * pow(a, n);
}

void note::calcTime(float tempo) { // tempo in bpm
    float tempLength = length;
    time = (tempLength/tempo)*60;
}

char note::getLetter() {
    return letter;
}
int note::getOctave() {
    return octave;
}
int note::getLength() {
    return length;
}
bool note::getSharp() {
    return sharp;
}
bool note::getFlat() {
    return flat;
}
float note::getFreq() {
    return freq;
}
float note::getTime() {
    return time;
}
