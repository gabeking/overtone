// Gabriel King
// buildSong.cpp will serve as lab06 deliverable, an attempt to load a song from ABC notation into Jeff's note/song ADTs

#include<iostream>
#include<fstream>
#include "song.h"
#include<string>

using namespace std;

int main(int argc, char *argv[]) {
  ifstream ifs;
  string linecur;
  song loaded;

  if (argc != 2) { // ensures proper usage
    cout << "Usage: " << argv[0] << " [FILE.abc]" << endl;
    return 1;
  }

  ifs.open(argv[1]); // loads file stream based on first argument

  if (!ifs) { // ensure valid file stream has been loaded
    cout << "The file name you entered, '" << argv[1] << "', is not valid!!" << endl;
    return 2;
  }

  while (getline(ifs, linecur)) { // incrementally loads each line of a file
    if (linecur.empty()) { // blank line is defined by ABC as the end of a file
      loaded.display();
      return 0; // all of song has successfully been loaded
    }
    switch (linecur.at(0)) {
      case '"': // eventually, this case will be modified to process note data
        break;
      case 'T':
        loaded.setTitle(linecur.substr(2)); // substr(2) will take the data after the header 'T:'
        break;      
      case 'C': // similarly, loads composer into song object
        loaded.setComposer(linecur.substr(2));
        break;      
      case 'M': // loads time signature into song object
        loaded.setM1(stoi(linecur.substr(2, 1))); // indices 2 and 4 will always correspond to numerator/denominator
        loaded.setM2(stoi(linecur.substr(4, 1))); // these values are cast to int with stoi()
        break;      
      case 'K':
        loaded.setKey(linecur.substr(2));
        break;
    }
  }

  loaded.display();

}
