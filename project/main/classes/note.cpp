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
note::note(int scrheight, double frequency, double onset) {
	freq = (int)frequency;
	onset_time = onset;
}

note::~note() {} // destructor


double note::getFreq() {
    return freq;
}
double note::getOnset() {
    return onset_time;
}
