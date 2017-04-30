/*  laser.h
 *  prototype for laser class
 *  Jeff Klouda CSE20312 Final Project
 */

#ifndef LASER_H
#define LASER_H

class laser : public sprite {
    public:
        laser(float, float, int, int, texture*);
        // updates position of sprite
        virtual void update();
        // returns true is still in window
        bool isOnScreen();
};

#endif
