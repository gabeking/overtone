#include <vector>
#include <cmath>
#include "note.h"
#include "texture.h"
#include "sprite.h"
#include "enemy.h"

int score_incrementer = 5;

static const double temp_sine_lookup[] = {0.121869, 0.241922, 0.358368, 0.469472, 0.573576, 0.669131, 0.75471, 0.829038, 0.891007, 0.939693, 0.97437, 0.994522, 0.999848, 0.990268, 0.965926, 0.927184, 0.87462, 0.809017, 0.731354, 0.642788, 0.544639, 0.438371, 0.325568, 0.207912, 0.0871557, -0.0348995, -0.156434, -0.275637, -0.390731, -0.5, -0.601815, -0.694658, -0.777146, -0.848048, -0.906308, -0.951057, -0.981627, -0.997564, -0.99863, -0.984808, -0.956305, -0.913545, -0.857167, -0.788011, -0.707107, -0.615661, -0.515038, -0.406737, -0.292372, -0.173648, -0.052336, 0.0697565};



const double* enemy::sine_lookup = temp_sine_lookup;
enemy::enemy(note enemy_note_info, int scrwidth, int scrheight, texture* spriteTexture) : sprite (scrwidth, scrheight, spriteTexture) {
    setVel(-10,0); // enemy class has inherited constructor, initializing velocity, acc, drag and position as appropriate for a not spawning on the right of the screen and moving left
    setPos(scrwidth, (int)enemy_note_info.getFreq()%(scrheight-height));
    xAcc = 0;
    yAcc = 0;
    maxVel = 10;
    maxAcc = 5;
    drag = 0.97;
	sine_counter=0;
	origin = y;
}

void enemy::update() {
    updatePos(); // standard position update on private members called
	setPos(x, origin+15*sine_lookup[sine_counter%50]);
	sine_counter++;
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


