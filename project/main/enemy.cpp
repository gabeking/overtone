#include <texture.h>
#include <vector>
#include <cmath>
#include "texture.h"
#include "sprite.h"
#include "enemy.h"

enemy::enemy() : sprite (texture*) {
    setVel(0,0);
    setPos(0,0);
    xAcc = 0;
    yAcc = 0;
    maxVel = 10;
    maxAcc = 5;
    drag = 0.97;
}

void enemy::update() {
    updateAcc();
    updateVel();
    updatePos();
}

void enemy::updateAcc(float dx, float dy) {
    xAcc += dx;
    yAcc += dy;
    float acc = xAcc*xAcc + yAcc*yAcc;
    if (acc > maxAcc) {
        xAcc *= sqrt(maxAcc/acc);
        yAcc *= sqrt(maxAcc/acc);
    }
}

void enemy::updateVel() {
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
