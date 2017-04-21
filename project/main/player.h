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
        virtual void update();
        void updateAcc();
        void updateVel();
    private:
        float xAcc;
        float yAcc;
        float maxVel;
        float maxAcc;
        float drag;
}
