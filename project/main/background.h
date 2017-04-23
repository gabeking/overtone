#ifndef BACKGROUND_H
#define BACKGROUND_H

class background : public sprite {
    public:
        background(float, int, int, texture*);
        virtual void update();
};

#endif
