#ifndef PLAYER_H
#define PLAYER_H

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

#include "texture.h"
#include <vector>
#include <SDL2/SDL.h>

class enemy : public sprite { // inherits from sprite class
    public:
        enemy(int, int, texture*);
        virtual void update();
        void updateAcc(float, float);
        void updateVel();
    private:
        float xAcc;
        float yAcc;
        float maxVel;
        float maxAcc;
        float drag;
};

#endif
