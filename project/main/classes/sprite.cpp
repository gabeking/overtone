/* sprite.cpp
 * Implementation for sprite object
 * Jeff Klouda
 */

#include "texture.h"
#include "sprite.h"
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <cmath>

sprite::sprite(int scrwidth, int scrheight, texture* spriteTexture) {
    
    this->spriteTexture = spriteTexture; // constructor initializes values
    width = spriteTexture->getWidth();
    height = spriteTexture->getHeight();
    
    x = 0; // defaults set
    y = 0;
    xVel = 0;
    yVel = 0;
    currentClip = NULL;
    clipNo = 0;            //current clip's position in clip vector
    sWidth = scrwidth;
    sHeight = scrheight;
    updateRadius(); // calculates estimated circular collision radius based on width and height
}

sprite::~sprite() {}

void sprite::render() {
    spriteTexture->render((int) x, (int) y, currentClip); // shortcut to render sprite
}

void sprite::nextClip(int nextClip) { // nextClip defaults to -1
    // no clips
    if (currentClip ==  NULL) {    // no clips
        return;
    }
    
    // automatically select next clip in vector if nextClip is default
    if (nextClip < 0) {       
        clipNo++;
        // reset clipNo if beyond end of clips vector
        if (clipNo >= (int) clips.size()) { 
            clipNo = 0;
        }
        currentClip = clips[clipNo]; 
    }
    
    // go to nextClip if nextClip is passed
    else {                   
        if (nextClip <= (int) clips.size()) {
            currentClip = clips[nextClip];
            clipNo = nextClip;
        }
    }
    width = currentClip->w;
    height = currentClip->h;
    updateRadius();
}

void sprite::setClips(std::vector<SDL_Rect*> clips) {
    this->clips = clips; //clipping rectangles updated given vector of new rectangle pointers
    currentClip = this->clips[0]; // current clip set to first position
    width = currentClip->w; // width and height updated based on current clip
    height = currentClip->h;
    updateRadius(); // collision radius updated
}

void sprite::updatePos() {
    x += xVel; // incrementally updated position based on dvelocity
    y += yVel;
}

void sprite::setPos(float x, float y) {
    this->x = x; // set function to modify position members
    this->y = y;
}

void sprite::setVel(float x, float y) {
    xVel = x; // set function to modify component velocity members
    yVel = y;
}

int sprite::getWidth() {
    return width; // get function returns width member
}

int sprite::getHeight() {
    return height; // get function returns height member
}

void sprite::updateRadius() {
    radius = (float) (width + height) / 4; // takes average of sprite width and height, which, divided by two, returns a radius that generally encases the sprite
}

float sprite::getX() {
    return x; // get function to return leftmost x position member
}

float sprite::getMidX() {
    return x + (float) width/2; // get function to return horizontal midpoint
}

float sprite::getY() {
    return y; // get function to return lowest y position
}

float sprite::getMidY() {
    return y + (float) height/2; // get function to return vertical midpoint
}

float sprite::getXVel() {
    return xVel; // get function to return horizontal vel member
}

float sprite::getYVel() {
    return yVel; // get function to return vertical vel member
}

float sprite::getRadius() {
    return radius; // get function to return radius member
}

void sprite::update(){}
