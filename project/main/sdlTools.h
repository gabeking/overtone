/* sdlTools.h
 * Essential functions and variables for SDL
 * Jeff Klouda - based on code from Lazy Foo' Productions (http://lazyfoo.net/)
 */

#ifndef SDLTOOLS_H
#define SDLTOOLS_H

#include <SDL2/SDL.h>
#include "texture.h"
#include <vector>

// Starts up SDL and creates window
bool init(SDL_Window*& gWindow, SDL_Renderer*& gRenderer, int screenWidth, int screenHeight);

// Shuts down SDL and frees loaded images
void close(TTF_Font*& gFont, SDL_Window*& gWindow, SDL_Renderer*& gRenderer, std::vector<texture>&);

// gmwindow = Window we'll render to
// gRenderer = The window renderer

// timer class - for all time-related needs
class SDLTimer {
    public:
        SDLTimer();

        void start();
        void stop();
        void pause();
        void unpause();

        Uint32 getTicks();

        bool isStarted();
        bool isPaused();
        
    private:
        // clock time when timer started
        Uint32 startTicks;

        // ticks stored when timer was paused
        Uint32 pausedTicks;

        //Timer status
        bool paused;
        bool started;
};

#endif
