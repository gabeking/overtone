/* collisons.cpp
 * implementation for collision checking function
 * Jeff Klouda
 */

#include <cmath>

#include "sprite.h"

bool checkColl(sprite* s1, sprite* s2) {
    // difference in sprite x midpoints
    float tempX = (s1->getMidX() - s2->getMidX());
    // difference in sprite y midpoints
    float tempY = (s1->getMidY() - s2->getMidY());
    tempX *= tempX;
    tempY *= tempY;
    // distance between center points is less than sum of raddii
    if (sqrt(tempX + tempY) < (s1->getRadius() + s2->getRadius())) {
        return true;
    }
    return false;
}
