#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<vector>

class Texture{

    public:

    SDL_Rect on_Screen;
    SDL_Texture* mTexture;
    SDL_Rect clip;
    double angle = 0;

    void Load_From_File(std::string path);

    void Set_Size(int w, int h);

    void Set_Position(int x, int y);

    void Set_Rect(int x, int y, int w, int h);

    void Set_Rotation(double degrees);

    void render();

    void free();
};

class Word_Texture{
    SDL_Rect on_Screen;
    SDL_Texture* mTexture;
    TTF_Font *gFont;
    SDL_Color gColor;
    std::string text;
    int number;
    bool is_Word;
public:

    void Load_Font(std::string font_path, int size);

    void Load_From_Text(std::string text);

    void Load_From_Number(int num);

    void Set_Position(int x, int y);

    void Set_Size(int w, int h);

    void Set_Color(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha);

    bool is_Clicked;
    void Handle_Event(SDL_Event *e);

    bool Is_inside(int x, int y);

    void render();

    void reset();

    void free();
};

void Init_Texture();

void Clean_Up();

#endif // TEXTURE_H_INCLUDED
