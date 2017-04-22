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
    
    this->spriteTexture = spriteTexture;
    width = spriteTexture->getWidth();
    height = spriteTexture->getHeight();
    
    x = 0;
    y = 0;
    xVel = 0;
    yVel = 0;
    currentClip = NULL;
    clipNo = 0;            //current clip's position in clip vector
    sWidth = scrwidth;
    sHeight = scrheight;
    updateRadius();
}

sprite::~sprite() {}

void sprite::render() {
    spriteTexture->render((int) x, (int) y, currentClip);
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
    this->clips = clips;
    currentClip = this->clips[0];
    width = currentClip->w;
    height = currentClip->h;
}

void sprite::updatePos() {
    x += xVel;
    y += yVel;
}

void sprite::setPos(float x, float y) {
    this->x = x;
    this->y = y;
}

void sprite::setVel(float x, float y) {
    xVel = x;
    yVel = y;
}

int sprite::getWidth() {
    return width;
}

int sprite::getHeight() {
    return height;
}

void sprite::updateRadius() {
    radius = (float) (width + height) / 2;
}

float sprite::getX() {
    return x;
}

float sprite::getMidX() {
    return x + (float) width/2;
}

float sprite::getY() {
    return y;
}

float sprite::getMidY() {
    return y + (float) height/2;
}

float sprite::getRadius() {
    return radius;
}
