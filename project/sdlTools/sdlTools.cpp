/* sdlTools.cpp
 * Essential functions and variables for SDL
 * Jeff Klouda - based on code from Lazy Foo' Productions (http://lazyfoo.net/)
 */

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
            // Initialize renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
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
