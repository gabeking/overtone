/* texture.h
 * class prototype for SDL texture
 * Jeff Klouda
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class texture {
    
    public:
        texture(SDL_Renderer*);
        ~texture();
        bool loadFromFile(std::string);                  // load image at path
        void free();                                // deallocate texture
        void render (int, int, SDL_Rect* = NULL);   // render cliiped image at x, y
        
        // get image dimensions
        int getWidth();
        int getHeight();
    
    private:
        SDL_Texture* mTexture;      // hardware texture
        SDL_Renderer* gRenderer;    // window renderer

        // image dimensions
        int mWidth;
        int mHeight;
};

#endif
