/* sprite.cpp
 * Implementation for sprite object
 * Jeff Klouda
 */

#include "texture.h"
#include "sprite.h"
#include <vector>
#include <SDL2/SDL.h>
#include <cmath>

sprite::sprite(texture* spriteTexture) {
    
    this->spriteTexture = spriteTexture;
    width = spriteTexture->getWidth();
    height = spriteTexture->getHeight();
    
    x = 0;
    y = 0;
    xVel = 0;
    yVel = 0;
    currentClip = NULL;
    clipNo = 0;            //current clip's position in clip vector
}

sprite::~sprite() {}

void sprite::render() {
    spriteTexture->render((int) x, (int) y, currentClip);
}

void sprite::nextClip(int nextClip = -1) {
    // no clips
    if (currentClip ==  NULL) {    // no clips
        return;
    }
    
    // reset clipNo if beyond end of clips vector
    if (clipNo >= (int) clips.size()) { 
        clipNo = -1;
    }
    // automatically select next clip in vector if nextClip is default
    if (nextClip < 0) {       
        currentClip = clips[++clipNo];
    }
    
    // go to nextClip if nextClip is passed
    else {                   
        if (nextClip <= (int) clips.size()) {
            currentClip = clips[nextClip];
            clipNo = nextClip;
        }
    }
}

void sprite::setClips(std::vector<SDL_Rect*> clips) {
    currentClip = clips[0];
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

int sprite:: getHeight() {
    return height;
}
