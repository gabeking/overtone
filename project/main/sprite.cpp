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
}

sprite::~sprite() {}

void sprite::render() {
    spriteTexture->render((int) x, (int) y, currentClip);
}

void sprite::nextClip(int nextClip = 0) {

}

void sprite::setClips(std::vector<SDL_Rect*> clips) {

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
