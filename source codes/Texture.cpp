#include "Texture.h"
#include "GamePlay.h"

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

Texture Space_Ship, gBackGround, Explosion, Rock, Bullet,
        Bullet_pack, Ship_Explosion, Bomb, Fast_shoot, Life, Score_background, Game_Logo;
Word_Texture Score, score_amount, Game_Over, Replay_but, Exit_but, Start_but,
             Main_Menu_but, Continue_but;

void Texture::Load_From_File(std::string path){
    free();
    SDL_Surface* loaded_Surface = IMG_Load(path.c_str());
    mTexture = SDL_CreateTextureFromSurface(gRenderer, loaded_Surface);
    clip.w = on_Screen.w = loaded_Surface->w;
    clip.h = on_Screen.h = loaded_Surface->h;
    SDL_FreeSurface(loaded_Surface);
}

void Texture::Set_Size(int w, int h){
    on_Screen.w = w;
    on_Screen.h = h;
}

void Texture::Set_Position(int x, int y){
    on_Screen.x = x;
    on_Screen.y = y;
}

void Texture::Set_Rect(int x, int y, int w, int h){
    clip = {x, y, w, h};
}

void Texture::Set_Rotation(double degrees){
    angle = degrees;
}

void Texture::render(){
    SDL_RenderCopyEx(gRenderer, mTexture, &clip, &on_Screen,
                      angle, NULL, SDL_FLIP_NONE);
}

void Texture::free(){
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
}

/////////////   class Word_Texture    ////////////////////////

void Word_Texture::Load_Font(std::string font_path, int size){
    gFont = TTF_OpenFont(font_path.c_str(), size);
}

void Word_Texture::Load_From_Text(std::string text_){
    text = text_;
    is_Word = true;
    free();
    SDL_Surface* loaded_Surface = TTF_RenderText_Solid(gFont, text_.c_str(), gColor);
    mTexture = SDL_CreateTextureFromSurface(gRenderer, loaded_Surface);
    on_Screen.w = loaded_Surface->w;
    on_Screen.h = loaded_Surface->h;
    SDL_FreeSurface(loaded_Surface);
}

void Word_Texture::Load_From_Number(int num){
    number = num;
    is_Word = false;
    free();
    std::stringstream num_text;
    num_text.str("");
    num_text << num;
    Load_From_Text(num_text.str().c_str());
}

void Word_Texture::Set_Position(int x, int y){
    on_Screen.x = x;
    on_Screen.y = y;
}

void Word_Texture::Set_Size(int w, int h){
    on_Screen.w = w;
    on_Screen.h = h;
}

void Word_Texture::Set_Color(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha)
{
    gColor = {r, g, b, alpha};
    if(is_Word == true){
        Load_From_Text(text);
    }
    else{
        Load_From_Number(number);
    }
}

void Word_Texture::Handle_Event(SDL_Event *e){
    if(e->type == SDL_MOUSEMOTION){
        // Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        if(!Is_inside(x, y)){    // mouse is outside of the button
            Set_Color(255, 255, 255, 255);
        }
        else{
            Set_Color(0, 255, 252, 255);
        }
    }
    if(e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT){
        int x, y;
        SDL_GetMouseState(&x, &y);

        if(Is_inside(x, y)){    // mouse is inside of the button
            is_Clicked = true;
        }
        else{
            is_Clicked = false;
        }
    }
}

bool Word_Texture::Is_inside(int x, int y){
    // Mouse if left of the button
    if( x < on_Screen.x )
    {
        return false;
    }
    //Mouse is right of the button
    if( x > on_Screen.x + on_Screen.w )
    {
        return false;
    }
    //Mouse above the button
    if( y < on_Screen.y )
    {
        return false;
    }
    //Mouse below the button
    if( y > on_Screen.y + on_Screen.h)
    {
        return false;
    }
    return true;
}

void Word_Texture::render(){
    SDL_RenderCopy(gRenderer, mTexture, NULL, &on_Screen);
}

void Word_Texture::reset(){
    is_Clicked = false;
    Set_Color(255, 255, 255, 255);
}

void Word_Texture::free(){
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
}

////////////////////////////////////////////////////////////

void Init_Texture(){
    Game_Logo.Load_From_File("image/game_logo.png");
    Game_Logo.Set_Position(290, 70);
    Space_Ship.Load_From_File("image/spaceship.png");
    Space_Ship.Set_Size(50, 60);
    gBackGround.Load_From_File("image/background.jpg");
    gBackGround.Set_Size(1200, 800);
    Explosion.Load_From_File("image/explosions/rock-explosion.png");
    Rock.Load_From_File("image/Rocks.png");
    Bullet.Load_From_File("image/blue_bullet.png");
    Bullet_pack.Load_From_File("image/bullet_icon.png");
    Ship_Explosion.Load_From_File("image/explosions/ship-explosion.png");
    Bomb.Load_From_File("image/Bomb.png");
    Fast_shoot.Load_From_File("image/Fast_shoot.png");
    Life.Load_From_File("image/life.png");
    Life.Set_Position(10, 10);
    Life.Set_Size(200, 55);
    Score_background.Load_From_File("image/Score_background.png");
    Score_background.Set_Position(220, 10);
    Score_background.Set_Size(300, 55);

    ////////////// Init Word_Texture ////////////////////
    Score.Load_Font("times-new-roman.ttf", 40);
    Score.Load_From_Text("SCORE:");
    Score.Set_Color(255, 255, 255, 255);
    Score.Set_Position(229, 14);
    score_amount.Load_Font("times-new-roman.ttf", 40);
    score_amount.Set_Position(400, 14);
    score_amount.Load_From_Number(0);
    score_amount.Set_Color(255, 255, 255, 255);
    Game_Over.Load_Font("times-new-roman.ttf", 90);
    Game_Over.Load_From_Text("GAME OVER!");
    Game_Over.Set_Color(255, 255, 255, 255);
    Game_Over.Set_Position(340, 200);
    Replay_but.Load_Font("times-new-roman.ttf", 40);
    Replay_but.Load_From_Text("REPLAY");
    Replay_but.Set_Color(255, 255, 255, 255);
    Replay_but.Set_Position(540, 400);
    Exit_but.Load_Font("times-new-roman.ttf", 40);
    Exit_but.Load_From_Text("EXIT");
    Exit_but.Set_Color(255, 255, 255, 255);
    Exit_but.Set_Position(548, 470);
    Start_but.Load_Font("times-new-roman.ttf", 40);
    Start_but.Load_From_Text("START");
    Start_but.Set_Position(530, 400);
    Start_but.Set_Color(255, 255, 255, 255);
    Main_Menu_but.Load_Font("times-new-roman.ttf", 40);
    Main_Menu_but.Load_From_Text("MAIN MENU");
    Main_Menu_but.Set_Color(255, 255, 255, 255);
    Main_Menu_but.Set_Position(500, 470);
    Continue_but.Load_Font("times-new-roman.ttf", 40);
    Continue_but.Load_From_Text("CONTINUE");
    Continue_but.Set_Color(255, 255, 255, 255);
    Continue_but.Set_Position(515, 330);
}

void Clean_Up(){
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;

    Game_Logo.free();
    gBackGround.free();
    Space_Ship.free();
    Explosion.free();
    Rock.free();
    Bullet.free();
    Bullet_pack.free();
    Ship_Explosion.free();
    Bomb.free();
    Fast_shoot.free();
    Life.free();
    Score_background.free();

    Score.free();
    score_amount.free();
    Game_Over.free();
    Replay_but.free();
    Exit_but.free();
    Start_but.free();
    Main_Menu_but.free();
    Continue_but.free();

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}