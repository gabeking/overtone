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
void close(SDL_Window*& gWindow, SDL_Renderer*& gRenderer, std::vector<texture>&);

// gmwindow = Window we'll render to
// gRenderer = The window renderer

#endif
