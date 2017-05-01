/* texture.cpp
 * implementation for SDL texture class
 * Jeff Klouda - based on code from Lazy Foo' Productions (http://lazyfoo.net/)
 */

#include "texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

// Global renderer
extern SDL_Renderer* gRenderer;

texture::texture() {
    mTexture = NULL;    // initalize texture pointer
    
    // initialize image dimensions
    mWidth = 0;
    mHeight = 0;
}

texture::~texture() {
    freeTexture();
}

bool texture::loadFromFile (std::string path) {
    freeTexture();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* lSurface = IMG_Load(path.c_str()); // loaded surface
    if (lSurface == NULL) {
        printf ("Unable to load image %s: SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else {
        // Color key image - SETS RGB 0, 255, 255 to be invisible
        SDL_SetColorKey (lSurface, SDL_TRUE, SDL_MapRGB(lSurface->format, 0, 0xFF, 0xFF));
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, lSurface);

        if (newTexture == NULL) {
            printf("Unable to create texture from %s: SDL Error: %s\n", 
                path.c_str(), SDL_GetError() );
        }
        else {
            //get image dimensions
            mWidth = lSurface->w;
            mHeight = lSurface->h;
        }
        // get rid of loaded surface
        SDL_FreeSurface( lSurface );
    }

    // return success
    mTexture = newTexture;
    return mTexture != NULL;
}

void texture::freeTexture() {
    //Free texture
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void texture::render (int x, int y, SDL_Rect* clip) {
    // Set rendering space
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    // set clip rendering dimensions
    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    // render to screen
    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

bool texture::loadFromRenderedText (TTF_Font* font, std::string text, SDL_Color textColor) {
    freeTexture(); // get rid of preexisting texture

    // render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (textSurface == NULL) {
        printf ("Unable to render text surface. SDL_ttf Error: %s\n", TTF_GetError());
    }
    else {
        // Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (mTexture == NULL) {
            printf("Unable to create texture from rendered text. SDL Error: %s\n", 
                SDL_GetError());
        }
        else {
            // get image dimensions 
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        // get rid of surface
        SDL_FreeSurface(textSurface);
    }

    // return success
    return (mTexture != NULL);
}

void texture::setColor (Uint8 red, Uint8 green, Uint8 blue) {
    // Modulate texture rgb (Change colors)
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

// Set blend mode 
// Set to SDL_BLENDMODE_BLEND for standard alpha blending
void texture::setBlendMode(SDL_BlendMode blendmode) {
    SDL_SetTextureBlendMode(mTexture, blendmode);
}

// Set alpha modulation (transparency)
// **REQUIRES blending to be enabled, ie. blend mode to be set to SDL_BLENDMODE_BLEND
// alpha = 255 opaque, alpha = 0 invisible
void texture::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

int texture::getWidth() {
    return mWidth;
}

int texture::getHeight() {
    return mHeight;
}
