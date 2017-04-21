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
    clip_no = 0;            //current clip's position in clip vector
}

sprite::~sprite() {}

void sprite::render() {
    spriteTexture->render((int) x, (int) y, currentClip);
}

void sprite::nextClip(int nextClip = -1) {
    if (current_clip ==  NULL) {    // no clips
        return;
    }
    if (nextClip < 0) {         // automatically select next clip in vector
    
    }
}

void sprite::setClips(std::vector<SDL_Rect*> clips) {
    current_clip = clips[0];
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
