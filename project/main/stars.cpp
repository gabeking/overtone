/* star.cpp
 *
 */
#include <random>
#include <list>
#include "stars.h"
#include "sprite.h"

star::star (int sW, int sH, texture* text) : sprite (sW, sH, text) {
    float scrollSpeed = -2;
    setPos(sW, rand() % sH);
    setVel(scrollSpeed, 0);
}

void star::update() {
    updatePos();
}

bool star::isOffScreen() {
    if (x < 0)
        return true;
    return false;
}

stars::stars(int sW, int sH, texture* text) {
    sWidth = sW;
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
    star_list.clear();
}

void stars::update() {
    if ((int)rand()%1000 <= spawn_rate) {
        star newStar(sWidth, sHeight, starText);
        star_list.push_back(newStar);
    }
    for (auto it = star_list.begin(); it != star_list.end();) {
        it->render();
        if (it->isOffScreen()) {
            it = star_list.erase(it);
            continue;
        }
        it->update();
        it++;
    }
}
