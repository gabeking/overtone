/* collisons.cpp
 * implementation for collision checking function
 * Jeff Klouda
 */

#include <cmath>

bool checkColl(float x1, float y1, float r1, float x2, float y2, float r2) {
    float tempX = (x1-x2) * (x1-x2);
    float tempY = (y1-y2) * (y1-y2);
    // distance between center points is less than sum of raddii
    if (sqrt(tempX + tempY) < (r1 + r2)) {
        return true;
    }
    return false;
}
