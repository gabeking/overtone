/* note.h
 * interface for note object for CSE20312 project
 * Jeff Klouda
 */

#ifndef NOTE_H
#define NOTE_H

class note {
    public:
        note(int, double, double);
        ~note();
        double getFreq(); // get frequency of note in Hz
        double getOnset(); // get length of note in sec
    private:
        double onset_time; // number of beats (eg. for 4/4 quarter note length = 1)
        double freq; // frequency of note in Hz
};

#endif
