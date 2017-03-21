/* note.h
 * interface for note object for CSE20312 project
 * Jeff Klouda
 */

#ifndef NOTE_H
#define NOTE_H

class note {
    public:
        note(char='c', int=4, int=1, bool=0, bool=0, float=60);
        ~note();

        void calcFreq(); // calculate frequency of note in Hz
        void calcTime(float); // calculate length of note in secs based on tempo

        char getLetter();
        int getOctave();
        int getLength();
        bool getSharp();
        bool getFlat();
        float getFreq(); // get frequency of note in Hz
        float getTime(); // get length of note in sec
    private:
        char letter; // which letter note it is
        int octave; // C 4 is middle C (C in abc notation)
        int length; // number of beats (eg. for 4/4 quarter note length = 1)
        bool sharp;
        bool flat;
        float freq; // frequency of note in Hz
        float time; // length of note in seconds
};

#endif
