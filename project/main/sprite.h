/* sprite.h
 * Interface for sprite object
 * Jeff Klouda
 */

#ifndef SPRITE_H
#define SPRITE_H

#include "texture.h"
#include <vector>
#include <SDL2/SDL.h>

class sprite { 
    public:
        sprite(texture*);
        ~sprite();
        virtual void update() = 0;
        void render();                      // render sprite
        void nextClip(int);                 // move to next clipping rectangle
        void setClips(std::vector<SDL_Rect*>);   // set clipping rectangles
        void updatePos();                   // update position based on velocity
        void updateVel(float, float);       // update velocity based on current velocity
        void setPos(float, float);          // set position
        void setVel(float, float);          // set velocity
        int getWidth();
        int getHeight();
    protected:
        texture* spriteTexture;
        std::vector<SDL_Rect*> clips;       // clipping rectangles
        SDL_Rect* currentClip;              // clipping rectangle to be rendered
        float x;
        float y;
        float xVel;                         // x velocity
        float yVel;                         // y velocity
        int width;
        int height;
};

#endif
