#include "Texture.h"
#include "GamePlay.h"
#include "Sound.h"
#include "Animation.h"
#include "MainMenu.h"
#include<ctime>

using namespace std;

SDL_Window* gWindow = SDL_CreateWindow("Space-Shooter",
                                       SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                       1200, 800, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
SDL_Renderer* gRenderer = SDL_CreateRenderer(gWindow, -1,
                                             SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

int main(int argv, char* argc[])
{
    srand(time(0));

    TTF_Init();
    Init_Sound();

    Init_Texture();
    Init_Animation();

    Main_Menu();

    Clean_Up();

    close_sound();

    return 0;
}
