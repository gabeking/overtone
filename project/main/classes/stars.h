/* stars.h
 * interface for drawing stars on background
 * Jeff Klouda CSE20312 Final Project
 */

#ifndef STARS_H
#define STARS_H

#include <list>
#include "sprite.h"

class star : public sprite {
    
    public:
        star(int, int, texture*);
        virtual void update();
        bool isOffScreen();
};

class stars {
    public:
        stars(int, int, texture*);
        ~stars();
        void update();
        int sWidth;
        int sHeight;
    private:
        texture* starText;
        std::list<star> star_list;
        int spawn_rate;         // out of 1000
};

#endif
