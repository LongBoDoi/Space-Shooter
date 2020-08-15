#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include "Texture.h"
#include <vector>

class animation{
    public:
        float Frame, speed;
        Texture t;
        int width, height;
        std::vector<SDL_Rect> frames;

        animation(){}

        animation(Texture t_, int x, int y, int w, int h, int Count, float Speed);
        // Count is the number of frames in the animation

        void Set_Size(int w, int h);

        void Update();

        void free();

        bool isEnd();
        // Check whether the animation has finished
};

void Init_Animation();

#endif // ANIMATION_H_INCLUDED
