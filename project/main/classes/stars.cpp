/* star.cpp
 *
 */
#include <random>
#include <list>
#include "stars.h"
#include "sprite.h"

star::star (int sW, int sH, texture* text) : sprite (sW, sH, text) {
    float scrollSpeed = -2; // stars initialized to random position/slow left scroll using inherited constructor
    setPos(sW, rand() % sH);
    setVel(scrollSpeed, 0);
}

void star::update() {
    updatePos(); // position update shortcut (using base class method)
}

bool star::isOffScreen() {
    if (x < 0) // check whether star should still be rendered
        return true;
    return false;
}

stars::stars(int sW, int sH, texture* text) {
    sWidth = sW; // populates stars when called, with density defined by spawn_rate. stored in list, which can easily have members popped when stars float offscreen
    sHeight = sH;
    starText = text;
    spawn_rate = 100;
    for (int i = 0; i < 20; i++) {
        star newStar(sWidth, sHeight, starText);
        newStar.setPos(rand()%sWidth, newStar.getY());
        star_list.push_back(newStar);
    }
}

stars::~stars() {
    star_list.clear(); // remove all stars
}

void stars::update() {
    if ((int)rand()%1000 <= spawn_rate) { // determines when to spawn new stars
        star newStar(sWidth, sHeight, starText);
        star_list.push_back(newStar);
    }
    for (auto it = star_list.begin(); it != star_list.end();) {
        it->render(); // actual deallocation/removal of "expired" stars
        if (it->isOffScreen()) {
            it = star_list.erase(it);
            continue;
        }
        it->update();
        it++;
    }
}
