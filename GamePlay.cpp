#include "GamePlay.h"
#include "Texture.h"
#include "Animation.h"
#include "Entity.h"
#include "Objects.h"
#include "Sound.h"
#include "MainMenu.h"

extern SDL_Renderer* gRenderer;

extern Texture Space_Ship, gBackGround, Explosion, Rock, Bullet,
                Bullet_pack, Ship_Explosion, Bomb, Fast_shoot, Life, Score_background;
extern Word_Texture Score, score_amount, Game_Over, Replay_but, Exit_but, Main_Menu_but;

extern animation sBullet, sExplosion, ship_explosion, sPlayer, sPlayer_dead, sPlayer_respawn,
            sBullet_pack, sBomb, sFast_shoot, sRock;

extern Mix_Chunk *Fire_sound, *explo_sound, *bonus_sound;

double DEGTORAD = 0.017453f;

std::list<Entity*> entities;
// All the objects will be stored in a list of Entity pointers

player *p;

SDL_Point Ship_Pos;
//// Ship_Pos is used to save the position of the player (space_ship)

float shoot_delay, shoot_speed;
float fast_shoot_time;
float respawn_time;
float delay_speed = 0.2;
//// These are the variables for getting delay to shoot, fast_shoot and respawn

bool game_paused;
// Check if the player pause the game

int Game_Play(){

    Life.Set_Rect(0, 3 * 64, 212, 64);
    score_amount.Load_From_Number(0);
    //// When starting a game, the player will have 3 lifes and the score is 0

    p = new player();
    p->settings(sPlayer, 200, 200, 0, 15);
    entities.push_back(p);
    //// Create a new player with the class player

    Ship_Pos = {500, 500};
    //// The starting position is 500 and 500

    shoot_delay = 0;
    fast_shoot_time = 0;
    respawn_time = 0;
    shoot_speed = 0.2;
    //// Set all the time delay to 0 and the shoot speed to 0.2

    SDL_Event e;
    bool game_over = false;
    game_paused = false;
    while(!game_over){
        while(SDL_PollEvent( &e ) != 0){
            if(e.type == SDL_QUIT){
                entities.clear();
                return 0;
            }
            if(e.type == SDL_MOUSEMOTION){
                SDL_GetMouseState(&Ship_Pos.x, &Ship_Pos.y);
                if(Ship_Pos.x > 1160) Ship_Pos.x = 1160;
                if(Ship_Pos.y > 760) Ship_Pos.y = 760;
                // We get the position of the space_ship using the motion of the mouse
                // and also make sure the space_ship stay within the screen
            }
            if(e.type == SDL_KEYDOWN){
                //if(e.key.keysym.sym == SDLK_q) game_over = true;
                if(e.key.keysym.sym == SDLK_ESCAPE){
                    game_paused = true;
                }
            }
        }

        //// Check game pause /////
        if(game_paused == true){
            game_paused = false;
            int selection = Pause_Menu(&e);
            if(selection == 1){
                entities.clear();
                return Game_Play();
            }
            if(selection == 2){
                entities.clear();
                return Main_Menu();
            }
            if(selection == 3){
                entities.clear();
                return 0;
            }
        }

        if(p->alive == true){

        shoot_speed = (p->fast_shoot_enabled == true ? 1.2 : 0.2);
        // if the player has fast shoot then the shooting speed is 1.2 else it is 0.2
        shoot_delay += shoot_speed;
        if(shoot_delay > 25){
            shoot_delay = 0;
            // reset the shoot delay time to 0 and create a new bullet;
            bullet *bul = new bullet();
            switch(p->bullet_num){
                case 1:
                    bul->settings(sBullet, Ship_Pos.x + 7, Ship_Pos.y, 0, 10);
                    break;
                case 2:
                    bul->settings(sBullet, Ship_Pos.x - 3, Ship_Pos.y, 0, 17);
                    break;
                case 3:
                    bul->settings(sBullet, (float)Ship_Pos.x - 12.2, Ship_Pos.y, 0, 30);
                    break;
            }
            // Check the amount of bullets that the player shoots each time
            entities.push_back(bul);
            Play_Sound(Fire_sound, 0);
        }
        }

        if(p->fast_shoot_enabled == true){
            fast_shoot_time += delay_speed;
            // if the player has fast shoot then start the time delay for fast shooting
            if(fast_shoot_time > 250){
                fast_shoot_time = 0;
                p->fast_shoot_enabled = false;
            }
            // When the delay is over reset to normal speed shooting
        }

        if(p->alive == false){  // When the player just die
            p->vulnerable = false;
            // The player will not be vulnerable
            respawn_time += delay_speed;
            // Then start the time delay for respawning
            if(respawn_time > 100){
                respawn_time = 0;
                p->settings(sPlayer_respawn, Ship_Pos.x, Ship_Pos.y, 0, 15);
                p->alive = true;
                // if the player respawns set the animation of respawning
                // and set him back to alive
            }
            else{
                if(p->revive == true){
                    p->revive = false;
                    p->settings(sPlayer_dead, Ship_Pos.x, Ship_Pos.y, 0, 15);
                    // if the player has not respawned then set the animation to death
                    // We use the variable p->revive to make sure the function settings
                    // above happens just once
                }
            }
        }

        if(p->anim.isEnd() == true){
            p->settings(sPlayer, Ship_Pos.x, Ship_Pos.y, 0, 15);
            p->vulnerable = true;
            // The space_ship only has the animation of respawning so this means
            // When the animation of respawning is over we set the animation back
            // to normal and make it vulnerable
        }

        Handle_Collision(game_over);

        p->Get_Position(Ship_Pos.x, Ship_Pos.y);
        // Set the position of the player according to the variable Ship_Pos

        for(auto a:entities){
            if(a->name == "explosion" || a->name == "ship_explosion"){
                if(a->anim.isEnd()) a->life = false;
            }
            // if the animation of exposions is over we destroy them so
            // that explosions only happen once
        }

        if (rand()%200==0)
        {
           asteroid *a = new asteroid();
           a->settings(sRock, rand() % 1150, 0, rand()%360, 25);
           entities.push_back(a);
        }
        // Randomly create a new asteroid

        if (rand() % 6000 == 0){
            package *bp = new package("bullet_pack");
            bp->settings(sBullet_pack, rand() % 1150, 0, 0, 35);
            entities.push_back(bp);
        }
        // Randomly create a new bullet package

        if (rand() % 7000 == 0){
            package *b = new package("bomb");
            b->settings(sBomb, rand() % 1150, 0, 0, 35);
            entities.push_back(b);
        }
        // Randomly create a new bomb package

        if (rand() % 6000 == 0){
            package *b = new package("fast_shoot");
            b->settings(sFast_shoot, rand() % 1150, 0, 0, 35);
            entities.push_back(b);
        }
        // Randomly create a new fast_shoot package

        for(auto i = entities.begin() ; i != entities.end() ; ){
            Entity *e = *i;
            e->update();
            e->anim.Update();
            // Update all the entities

            if(e->life == false){
                i = entities.erase(i);
                delete e;
            }
            // Destroy entities
            else i++;
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

        SDL_RenderPresent(gRenderer);
    }

    ////////////// Game over screen ////////////////////

    Exit_but.Set_Position(570, 540);

    while(true){
        while(SDL_PollEvent( &e ) != 0){
            if(e.type == SDL_QUIT){
                entities.clear();
                return 0;
            }
            Replay_but.Handle_Event( &e );
            Exit_but.Handle_Event( &e );
            Main_Menu_but.Handle_Event( &e );
            if(Replay_but.is_Clicked == true){
                Replay_but.reset();
                entities.clear();
                return Game_Play();
            }
            if(Exit_but.is_Clicked == true){
                Exit_but.reset();
                entities.clear();
                return 0;
            }
            if(Main_Menu_but.is_Clicked == true){
                Main_Menu_but.reset();
                entities.clear();
                return Main_Menu();
            }
        }
        for(auto i = entities.begin() ; i != entities.end() ; ){
            Entity *e = *i;

            for(auto a:entities){
                if(a->name == "ship_explosion"){
                    if(a->anim.isEnd()) a->life = false;
                }
            }

            if(e->name == "ship_explosion") e->anim.Update();

            if(e->life == false || e->name == "bullet" || e->name == "explosion"){
                i = entities.erase(i);
                delete e;
                // Destroy dead entities, all bullets and asteroid explosion
            }
            else i++;
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
        Game_Over.render();
        Replay_but.render();
        Main_Menu_but.render();
        Exit_but.render();

        SDL_RenderPresent(gRenderer);
    }
}
