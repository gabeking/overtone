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
        sprite(int, int, texture*);         // screen wd screen ht texture
        ~sprite();
        void render();                      // render sprite
        
        // update functions
        virtual void update();
        void updatePos();                   // update position based on velocity
        void updateVel(float, float);       // update velocity based on current velocity
        void updateRadius();                // set radius based on height and width
        void nextClip(int=-1);              // move to next clipping rectangle
        
        // set functions
        void setPos(float, float);          // set position
        void setVel(float, float);          // set velocity
        void setClips(std::vector<SDL_Rect*>);   // set clipping rectangles
        
        // get functions
        int getWidth();
        int getHeight();
        float getX();
        float getMidX();                    // get x midpoint
        float getY();
        float getMidY();                    // get y midpoint
        float getXVel();
        float getYVel();
        float getRadius();
    
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
        int clipNo;                         // currentClip's position in clips
        int sWidth;                         // screen width
        int sHeight;                        // screen height
        float radius;                       // raidus for collison checking
                                            // rad = avg(width and height)
};

#endif
