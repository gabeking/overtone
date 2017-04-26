/* songTest.cpp
 * driver to test song ADT
 * Jeff Klouda
 */

#include <string>
#include <iostream>
#include "song.h"

using namespace std;

int main() {
    // test song object
    song testSong1; // check default constructor
    cout << "testSong1\n";
    testSong1.display();
    
    cout << "\ntestSong2\n";
    song testSong2("Title","Composer", 6, 8, "C", 120);
    
    note newNote1; // should use default note values
    note newNote2('a',4,1,0,0,testSong2.tempo);
    note newNote3('c',2,2,0,0,testSong2.tempo);
    testSong2.addNote(newNote1);
    testSong2.addNote(newNote2);
    testSong2.addNote(newNote3);

    testSong2.display();
    
    cout << endl;
    // test note object
    cout << newNote1.getFreq() << " " << newNote1.getTime() << endl;
    cout << newNote2.getFreq() << " " << newNote2.getTime() << endl;
    cout << newNote3.getFreq() << " " << newNote3.getTime() << endl;
    return 0;
}
