/* player.cpp
 * class implementation for player object
 * Jeff Klouda CSE20312 Overtone
 */

#include <texture.h>
#include <vector>
#include <cmath>
#include "texture.h"
#include "sprite.h"
#include "player.h"

player::player() : sprite (texture*) {
    setVel(0,0);
    setPos(0,0);
    xAcc = 0;
    yAcc = 0;
    maxVel = 10;
    maxAcc = 5;
    drag = 0.97;
}

void player::update() {
    Uint8 *keystates = SDL_GetKeyState(NULL);
    if (keystates[SDLK_UP]) {

    }
    if (keystates[SDLK_DOWN]) {
    
    }
    if (keystates[SDLK_LEFT]) {

    }
    if (keystates[SDLK_RIGHT]) {

    }
    updateAcc();
    updateVel();
    updatePos();
}

void player::updateAcc(float dx, float dy) {
    xAcc += dx;
    yAcc += dy;
    float acc = xAcc*xAcc + yAcc*yAcc;
    if (acc > maxAcc) {
        xAcc *= sqrt(maxAcc/acc);
        yAcc *= sqrt(maxAcc/acc);
    }
}

void player::updateVel() {
    xVel += xAcc;
    yVel += yAcc;
    float vel = xVel*xVel + yVel*yVel;
    if (vel > maxVel) { // limit velocity to max
        xVel *= sqrt(maxVel/vel);
        yVel *= sqrt(maxVel/vel);
    }

    xVel *= drag;
    yVel *= drag;
}
