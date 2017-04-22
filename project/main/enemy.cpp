#include <vector>
#include <cmath>
#include "note.h"
#include "texture.h"
#include "sprite.h"
#include "enemy.h"



enemy::enemy(note enemy_note_info, int scrwidth, int scrheight, texture* spriteTexture) : sprite (scrwidth, scrheight, spriteTexture) {
    setVel(-5,0);
    setPos(scrwidth, enemy_note_info.getFreq());
    xAcc = 0;
    yAcc = 0;
    maxVel = 10;
    maxAcc = 5;
    drag = 0.97;
}

void enemy::update() {
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
