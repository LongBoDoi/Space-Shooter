#include "MainMenu.h"
#include "Texture.h"
#include "Objects.h"
#include "GamePlay.h"

extern SDL_Renderer* gRenderer;

extern animation sRock;

extern Texture Game_Logo, gBackGround, Life, Score_background, Life_2, Score_background_2,
        Overheat_frame_2, Overheat_2, Boss_health_frame, Boss_health_bar, Overheat_1,
        Overheat_frame_1;
extern Word_Texture Start_but, Exit_but, Replay_but, Main_Menu_but, Continue_but, High_Score_but,
        score_amount, Score, Single_Play, Duel_Play, Game_Version, Score_2, score_amount_2,
        Boss_HP;

extern bool boss_appearing;

extern std::list<Entity*> entities;

int Main_Menu(){

    SDL_ShowCursor(SDL_ENABLE);

    std::list<Entity*> floating_rock;

    for(int i = 0 ; i < 10 ; i++){
        asteroid *a = new asteroid();
        a->settings(sRock, rand() % 1200, rand() % 800);
        floating_rock.push_back(a);
    }

    Exit_but.Set_Position(545, 540);

    SDL_Event e;
    while(true){
        while(SDL_PollEvent( &e ) != 0){
            if(e.type == SDL_QUIT){
                floating_rock.clear();
                return -1;
            }
            Start_but.Handle_Event( &e );
            High_Score_but.Handle_Event( &e );
            Exit_but.Handle_Event( &e );
            if(Start_but.is_Clicked == true){
                floating_rock.clear();
                Start_but.reset();
                return Play_Mode_Menu();
            }
            if(Exit_but.is_Clicked == true){
                floating_rock.clear();
                Exit_but.reset();
                return -1;
            }
            if(High_Score_but.is_Clicked == true){
                floating_rock.clear();
                High_Score_but.reset();
                return Display_High_Scores();
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
        High_Score_but.render();
        Game_Version.render();
        SDL_RenderPresent(gRenderer);
    }
}

int Play_Mode_Menu(){
    SDL_ShowCursor(SDL_ENABLE);

    SDL_Event e;
    while(true){
        while(SDL_PollEvent( &e ) != 0){
            if(e.type == SDL_QUIT){
                return -1;
            }
            Single_Play.Handle_Event( &e );
            Duel_Play.Handle_Event( &e );
            if(Single_Play.is_Clicked == true){
                Single_Play.reset();
                return Game_Play(false);
            }
            if(Duel_Play.is_Clicked == true){
                Duel_Play.reset();
                return Game_Play(true);
            }
            if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_ESCAPE) return Main_Menu();
            }
        }
        SDL_RenderClear(gRenderer);\

        gBackGround.render();
        Game_Logo.render();
        Single_Play.render();
        Duel_Play.render();
        SDL_RenderPresent(gRenderer);
    }
}

int Pause_Menu(SDL_Event *e, bool duel_play){
    SDL_ShowCursor(SDL_ENABLE);

    Exit_but.Set_Position(567, 540);
    const Uint8* currentKeyState = SDL_GetKeyboardState( NULL );
    while(true){
        if( currentKeyState[ SDL_SCANCODE_ESCAPE ] ){
        //if(e.key.keysym.sym == SDLK_q) game_over = true;
            return 0;
        }
        while(SDL_PollEvent(e) != 0){
            if(e->type == SDL_QUIT) return 3;
            Continue_but.Handle_Event(e);
            Replay_but.Handle_Event(e);
            Main_Menu_but.Handle_Event(e);
            Exit_but.Handle_Event(e);
            if(Continue_but.is_Clicked == true){
                SDL_ShowCursor(SDL_DISABLE);
                Continue_but.reset();
                return 0;
            }
            if(Replay_but.is_Clicked == true){
                SDL_ShowCursor(SDL_DISABLE);
                Replay_but.reset();
                return 1;
            }
            if(Main_Menu_but.is_Clicked == true){
                SDL_ShowCursor(SDL_DISABLE);
                Main_Menu_but.reset();
                return 2;
            }
            if(Exit_but.is_Clicked == true){
                SDL_ShowCursor(SDL_DISABLE);
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
        Overheat_frame_1.render();
        Overheat_1.render();

        if(duel_play == true){
            Life_2.render();
            Score_background_2.render();
            Score_2.render();
            score_amount_2.render();
            Overheat_frame_2.render();
            Overheat_2.render();
        }
        if(boss_appearing == true){
            Boss_health_frame.render();
            Boss_health_bar.render();
            Boss_HP.render();
        }

        Continue_but.render();
        Replay_but.render();
        Main_Menu_but.render();
        Exit_but.render();

        SDL_RenderPresent(gRenderer);
    }
}

int Display_High_Scores(){
    ifstream get_high_score;
    get_high_score.open("High_Score.txt");

    std::vector<std::string> scores;
    for(int i = 0 ; i < 10 ; i++){
        string info;
        getline(get_high_score, info);
        scores.push_back(info);
    }
    get_high_score.close();

    std::list<Word_Texture*> tHigh_score;
    for(int i = 0 ; i < 10 ; i++){
        auto data = new Word_Texture();
        data->Load_Font("times-new-roman.ttf", 40);
        data->Load_From_Text(scores[i]);
        data->Set_Color(255, 255, 255, 255);
        data->Set_Position(i != 9 ? 560 : 540, i*50 + 150);
        tHigh_score.push_back(data);
    }

    SDL_Event e;
    while(true){
        while(SDL_PollEvent( &e ) != 0){
            if(e.type == SDL_QUIT){
                scores.clear();
                for(auto i:tHigh_score){
                    i->free();
                }
                tHigh_score.clear();
                return -1;
            }
            if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_ESCAPE){
                    scores.clear();
                    for(auto i:tHigh_score){
                        i->free();
                    }
                    tHigh_score.clear();
                    return Main_Menu();
                }
            }
        }
        SDL_RenderClear(gRenderer);

        gBackGround.render();
        for(auto i:tHigh_score){
            i->render();
        }
        SDL_RenderPresent(gRenderer);
    }
}

void Update_High_Score(int new_score){
    ifstream get_high_score;
    get_high_score.open("High_Score.txt");
    std::vector<int> scores;
    for(int i = 0 ; i < 10 ; i++){
        int index;
        get_high_score >> index;
        char dot;
        get_high_score >> dot;
        int score;
        get_high_score >> score;
        scores.push_back(score);
    }
    scores.push_back(new_score);
    sort(scores.begin(), scores.end());
    scores.erase(scores.begin());

    get_high_score.close();

    ofstream add_high_score;
    add_high_score.open("High_Score.txt");
    for(int i = 9 ; i >= 0 ; i--){
        add_high_score << 10 - i << ". " << scores[i] << endl;
    }

    add_high_score.close();

    scores.clear();
}
