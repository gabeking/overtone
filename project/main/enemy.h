#ifndef PLAYER_H
#define PLAYER_H

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

#include "texture.h"
#include <vector>
#include <SDL2/SDL.h>

class enemy : public sprite { // inherits from sprite class
    public:
        enemy (double cost=0.0, int id=0)
        : Base(id), // work in progress, using non default constructor
        VARNMAE(varvlue)
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
