#include "MainMenu.h"
#include "Texture.h"
#include "Objects.h"
#include "GamePlay.h"

extern SDL_Renderer* gRenderer;

extern animation sRock;

extern Texture Game_Logo, gBackGround, Life, Score_background;
extern Word_Texture Start_but, Exit_but, Replay_but, Main_Menu_but, Continue_but,
        score_amount, Score;

extern std::list<Entity*> entities;

int Main_Menu(){

    std::list<Entity*> floating_rock;

    for(int i = 0 ; i < 10 ; i++){
        asteroid *a = new asteroid();
        a->settings(sRock, rand() % 1200, rand() % 800);
        floating_rock.push_back(a);
    }

    Exit_but.Set_Position(548, 470);

    SDL_Event e;
    while(true){
        while(SDL_PollEvent( &e ) != 0){
            if(e.type == SDL_QUIT){
                floating_rock.clear();
                return -1;
            }
            Start_but.Handle_Event( &e );
            Exit_but.Handle_Event( &e );
            if(Start_but.is_Clicked == true){
                floating_rock.clear();
                Start_but.reset();
                return Game_Play();
            }
            if(Exit_but.is_Clicked == true){
                floating_rock.clear();
                Exit_but.reset();
                return -1;
            }
        }
        SDL_RenderClear(gRenderer);

        for(auto i:floating_rock){
            i->anim.Update();
        }

        gBackGround.render();
        for(auto i:floating_rock){
            i->draw();
        }
        Game_Logo.render();
        Start_but.render();
        Exit_but.render();
        SDL_RenderPresent(gRenderer);
    }
}

int Pause_Menu(SDL_Event *e){
    Exit_but.Set_Position(567, 540);
    while(true){
        while(SDL_PollEvent(e) != 0){
            if(e->type == SDL_KEYDOWN){
                if(e->key.keysym.sym == SDLK_ESCAPE){
                    return 0;
                }
            }
            if(e->type == SDL_QUIT) return 3;
            Continue_but.Handle_Event(e);
            Replay_but.Handle_Event(e);
            Main_Menu_but.Handle_Event(e);
            Exit_but.Handle_Event(e);
            if(Continue_but.is_Clicked == true){
                Continue_but.reset();
                return 0;
            }
            if(Replay_but.is_Clicked == true){
                Replay_but.reset();
                return 1;
            }
            if(Main_Menu_but.is_Clicked == true){
                Main_Menu_but.reset();
                return 2;
            }
            if(Exit_but.is_Clicked == true){
                Exit_but.reset();
                return 3;
            }
        }

        SDL_RenderClear(gRenderer);

        gBackGround.render();

        for(auto i:entities){
            i->draw();
        }

        Life.render();
        Score_background.render();
        Score.render();
        score_amount.render();

        Continue_but.render();
        Replay_but.render();
        Main_Menu_but.render();
        Exit_but.render();

        SDL_RenderPresent(gRenderer);
    }
}
