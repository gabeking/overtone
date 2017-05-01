#ifndef ENEMY_H
#define ENEMY_H

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

#include "sprite.h"
#include "texture.h"
#include "note.h"
#include <vector>
#include <SDL2/SDL.h>

class enemy : public sprite { // inherits from sprite class
    public:
        enemy(note, int, int, texture*);
        virtual void update();
        void updateAcc(float, float);
        void updateVel();
		int  enemy_dies(int);
		const static double* sine_lookup;
    private:
        float xAcc;
        float yAcc;
        float maxVel;
        float maxAcc;
        float drag;
		int sine_counter;
		double origin;
};

#endif
