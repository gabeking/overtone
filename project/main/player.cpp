/* player.cpp
 * class implementation for player object
 * Jeff Klouda CSE20312 Overtone
 */

#include <vector>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.h"
#include "sprite.h"
#include "player.h"

player::player (float x, float y, texture* text) : sprite (text) {
    setVel(0,0);
    setPos(x,y);
    maxVel = 15;
    drag = 0.95;
    acc = 1.2;
}

void player::update() {
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    float dx = 0, dy = 0;           // changes in acceleration
    if (keystates[SDL_SCANCODE_UP]) {
        dy -= acc;
    }
    if (keystates[SDL_SCANCODE_DOWN]) {
        dy += acc;
    }
    if (keystates[SDL_SCANCODE_LEFT]) {
        dx -= acc;
    }
    if (keystates[SDL_SCANCODE_RIGHT]) {
        dx += acc;
    }
    nextClip();
    updateVel(dx, dy);
    updatePos();
}

void player::updateVel(float dx, float dy) {
    xVel += dx;
    yVel += dy;
    float vel = xVel*xVel + yVel*yVel;
    if (vel > maxVel) { // limit velocity to max
        xVel *= sqrt(maxVel/vel);
        yVel *= sqrt(maxVel/vel);
    }

    xVel *= drag;
    yVel *= drag;
}
