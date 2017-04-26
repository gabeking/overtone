#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>

// REFERENCED GIT GIST https://gist.github.com/cdave1/10563386 

using std::string;
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv) {
  char *song = new char[BUFSIZ];

  cout << "Please enter the name of your song file, including .mp3" << endl;

  cin >> song;

  int res = 0;
  int flags = MIX_INIT_MP3;

  if (SDL_Init(SDL_INIT_AUDIO < 0)) {
    cout << "SDL Failed to Initialize" << endl;
    exit(1);
  } 

  res = Mix_Init(flags);

  if (flags != res) {
    cout << "Could not initialize mixer, result: " << res;
    exit(1);
  }

  Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
  Mix_Music *mus = Mix_LoadMUS(song);
  Mix_PlayMusic(mus, 1);

  while (!SDL_QuitRequested()) {
    SDL_Delay(250);
  }

  Mix_FreeMusic(mus);
  SDL_Quit();

  delete [] song;
  return 0;

}

