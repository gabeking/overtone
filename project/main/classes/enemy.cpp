#include <vector>
#include <cmath>
#include "note.h"
#include "texture.h"
#include "sprite.h"
#include "enemy.h"

int score_incrementer = 5;

enemy::enemy(note enemy_note_info, int scrwidth, int scrheight, texture* spriteTexture) : sprite (scrwidth, scrheight, spriteTexture) {
    setVel(-10,0); // enemy class has inherited constructor, initializing velocity, acc, drag and position as appropriate for a not spawning on the right of the screen and moving left
    setPos(scrwidth, (int)enemy_note_info.getFreq()%(scrheight-height));
    xAcc = 0;
    yAcc = 0;
    maxVel = 10;
    maxAcc = 5;
    drag = 0.97;
}

void enemy::update() {
    updatePos(); // standard position update on private members called

}

void enemy::updateAcc(float dx, float dy) {
    xAcc += dx; // component acceleration updated given x and y differentials -- verified to not exceed defined maxAcc
    yAcc += dy;
    float acc = xAcc*xAcc + yAcc*yAcc;
    if (acc > maxAcc) {
        xAcc *= sqrt(maxAcc/acc);
        yAcc *= sqrt(maxAcc/acc);
    }
}

void enemy::updateVel() {
    xVel += xAcc; // component velocity updated using acceleration members
    yVel += yAcc;
    float vel = xVel*xVel + yVel*yVel;
    if (vel > maxVel) { // limit velocity to max
        xVel *= sqrt(maxVel/vel);
        yVel *= sqrt(maxVel/vel);
    }

    xVel *= drag; // drag factor applied
    yVel *= drag;
}


