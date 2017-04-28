/* player.cpp
 * class implementation for player object
 * Jeff Klouda CSE20312 Overtone
 */

#include <vector>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "texture.h"
#include "sprite.h"
#include "player.h"

player::player (float x, float y, int width, int height, texture* text) : sprite (width, height, text) {
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
    updateVel(dx, dy);
    updatePos();
    if ((int)this->x <= 0)
        setPos(0, this->y);
    if ((int)this->y <= 0)
        setPos(this->x, 0);
    if ((int)this->x + this->width >= sWidth)
        setPos(sWidth - this->width, this->y);
    if ((int)this->y + this->height >= sHeight)
        setPos(this->x, sHeight - this->height);
    /*
    std::cout << "\nx = " << x << "\ny = " << y;
    std::cout << "\nwidth = " << width;
    std::cout << "\nheight = " << height;
    std::cout << "\nsWidth = " << sWidth;
    std::cout << "\nsHeight = " << sHeight;
    */
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
