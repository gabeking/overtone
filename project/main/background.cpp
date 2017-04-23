#include "sprite.h"
#include "background.h"


// note: background must be same size as window
background::background(float xVel, int sW, int sH, texture* text) :
sprite(sW, sH, text) {
    setVel(xVel, 0);
}

void background::update() {
    if (x + width <= 0) {
        setPos(width, 0);
    }
    else {
        x -= 1;
    }
}
