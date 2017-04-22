/* sdlTools.cpp
 * Essential functions and variables for SDL
 * Jeff Klouda - based on code from Lazy Foo' Productions (http://lazyfoo.net/)
 */

// TODO Adapt loadMedia() function from test.cpp (maybe store sprites in a vector?

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sdlTools.h"
#include "texture.h"
#include <stdio.h>
#include <vector>

bool init(SDL_Window*& gWindow, SDL_Renderer*& gRenderer, int screenWidth, int screenHeight) {
    //initializiation flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize. SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled");
        }

        // Create window
        gWindow = SDL_CreateWindow("Operation Overtone", SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

        if (gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            // Initialize renderer for window with vsync enabled
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | 
                SDL_RENDERER_PRESENTVSYNC);
            
            if (gRenderer == NULL) {
                printf("Renderer could not be created. SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else {
                // Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if ( !( IMG_Init( imgFlags ) & imgFlags ) ) {
                    printf ("SDL_image could not initialize. SDL_image Error: %s\n",
                        IMG_GetError() );
                    success = false;
                }
            }
        }
    }
    return success;
}

void close(SDL_Window*& gWindow, SDL_Renderer*& gRenderer, std::vector<texture>& textures) {
    
    // Free loaded images passed as vector
    for (std::vector<texture>::iterator it = textures.begin(); it != textures.end(); it++) {
        it->freeTexture();
    }
    
    // Destroy window
    SDL_DestroyRenderer (gRenderer);
    SDL_DestroyWindow (gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDLTimer::SDLTimer() {
    startTicks = 0;
    pausedTicks = 0;

    paused = false;
    started = false;
}

void SDLTimer::start() {
    
    // start timer
    started = true;
    
    // unpause
    paused = false;
    
    // get current clock time
    startTicks = SDL_GetTicks();
    
    // reset time since paused
    pausedTicks = 0;
}

void SDLTimer::stop(){
    // stop the timer
    started = false;

    //unpause the timer
    paused = false;

    // clear tick variables
    startTicks = 0;
    pausedTicks = 0;
}

void SDLTimer::pause() {
    if (started && !paused) {
        paused = true;

        pausedTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void SDLTimer::unpause() {
    if (started && paused) {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

Uint32 SDLTimer::getTicks() {
    Uint32 time = 0;

    if (started) {
        if (paused) {
            time = pausedTicks;
        }
        else {
            time = SDL_GetTicks() - startTicks;
        }
    }

    return time;
}

bool SDLTimer::isStarted() {
    return started;
}

bool SDLTimer::isPaused() {
    return paused && started;
}
