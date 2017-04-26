/*  player.h
 *
 *  Jeff Klouda CSE20312 Overtone
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "texture.h"
#include <vector>
#include <SDL2/SDL.h>

class player : public sprite { // inherits from sprite class

    public:
        player(float,float, int, int, texture*);
        virtual void update();
        void updateVel(float, float);
    private:
        float acc;
        float maxVel;
        float drag;
};

#endif