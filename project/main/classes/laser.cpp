/* laser.cpp
 * implementation of laser class
 * Jeff Klouda CSE20312 Final Project
 */

#include "sprite.h"
#include "laser.h"

laser::laser(float xVel, float yVel, int sW, int sH, 
texture* text) : sprite (sW, sH, text) {
    setVel(xVel, yVel);
}

void laser::update() {
    updatePos();
}

bool laser::isOnScreen() { // if x and y position are properly confined within screen boundaries, TRUE, else, FALSE
    if (x < 0 || y < 0 || (int) x + width > sWidth || 
    (int) y + height > sHeight)
    {
        return false;
    }
    else {
        return true;
    }
}
