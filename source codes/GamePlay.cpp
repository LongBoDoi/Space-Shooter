#include "GamePlay.h"
#include "Texture.h"
#include "Animation.h"
#include "Entity.h"
#include "Objects.h"
#include "Sound.h"
#include "MainMenu.h"

extern SDL_Renderer* gRenderer;

extern Texture Space_Ship, gBackGround, Explosion, Rock, Bullet,
                Bullet_pack, Ship_Explosion, Bomb, Fast_shoot, Life, Score_background,
                Life_2, Score_background_2, Overheat_1, Overheat_2,
                Overheat_frame_1, Overheat_frame_2;
extern Word_Texture Score, score_amount, Game_Over, Replay_but, Exit_but,
        Main_Menu_but, Score_2, score_amount_2, p1_id, p2_id;

extern animation sBullet, sExplosion, ship_explosion, sPlayer, sPlayer_dead, sPlayer_respawn,
            sBullet_pack, sBomb, sFast_shoot, sRock, sBullet_2;

extern Mix_Chunk *Fire_sound, *explo_sound, *bonus_sound;




std::list<Entity*> entities;
// All the objects will be stored in a list of Entity pointers

player *p, *p2;

SDL_Point Ship_Pos, Ship_Pos_2;
//// Ship_Pos is used to save the position of the player (space_ship)

float shoot_delay, shoot_delay_2, shoot_speed, shoot_speed_2;
float fast_shoot_time, fast_shoot_time_2;
float respawn_time, respawn_time_2;
float delay_speed = 0.2;
//// These are the variables for getting delay to shoot, fast_shoot and respawn

bool game_paused;
bool p1_dead, p2_dead;
// Check if the player pause the game

int final_score_1, final_score_2;

int Game_Play(bool duel_play){

    SDL_ShowCursor(SDL_DISABLE);

    Life.Set_Rect(0, 3 * 64, 212, 64);
    Life_2.Set_Rect(0, 3*64, 212, 64);
    score_amount.Load_From_Number(0);
    //// When starting a game, the player will have 3 lifes and the score is 0

    p = new player();
    p->settings(sPlayer, 200, 200, 0, 15);
    entities.push_back(p);
    p2 = new player();
    if(duel_play == true) p2->settings(sPlayer, 200, 200, 0, 15);
    else p2->settings(sPlayer_dead, 200, 200, 0, 15);
    entities.push_back(p2);
    //// Create a new player with the class player

    final_score_1 = final_score_2 = 0;

    Ship_Pos = {500, 500};
    Ship_Pos_2 = {1000, 500};
    //// The starting position is 500 and 500

    shoot_delay = shoot_delay_2 = 0;
    fast_shoot_time = fast_shoot_time_2 = 0;
    respawn_time = respawn_time_2 = 0;
    shoot_speed = shoot_speed_2 = 0.2;
    //// Set all the time delay to 0 and the shoot speed to 0.2

    game_paused = false;

    SDL_Event e;
    const Uint8* currentKeyState = SDL_GetKeyboardState( NULL );
    const Uint8* currentKeyState_2 = SDL_GetKeyboardState( NULL );
    bool game_over = false;
    p1_dead = p2_dead = false;
    bool p1_shooting = false, p2_shooting = false;
    double p1_overheat_lv = 0, p2_overheat_lv = 0;
    bool p1_overheated = false, p2_overheated = false;
    double p1_overheat_cooldown = 0, p2_overheat_cooldown = 0;
    while(!game_over){
        if( currentKeyState[ SDL_SCANCODE_W ] ){
            Ship_Pos.y -= p->move_speed;
            if(Ship_Pos.y < 0) Ship_Pos.y = 0;
        }
        if( currentKeyState[ SDL_SCANCODE_A ] ){
            Ship_Pos.x -= p->move_speed;
            if(Ship_Pos.x < 0) Ship_Pos.x = 0;
        }
        if( currentKeyState[ SDL_SCANCODE_S ] ){
            Ship_Pos.y += p->move_speed;
            if(Ship_Pos.y > 750) Ship_Pos.y = 750;
        }
        if( currentKeyState[ SDL_SCANCODE_D ] ){
            Ship_Pos.x += p->move_speed;
            if(Ship_Pos.x > 1150) Ship_Pos.x = 1150;
        }
        if( currentKeyState[ SDL_SCANCODE_SPACE ] ){
            if(p->alive == false && p1_overheated == false){
                p1_overheat_lv-=0.15;
                if(p1_overheat_lv < 0) p1_overheat_lv = 0;
            }
            p1_shooting = true;
            if(p1_overheated == false && p->alive == true)
                p1_overheat_lv += 0.15;
            if(p1_overheat_lv >= 100){
                p1_overheat_lv = 100;
                p1_overheated = true;
            }
        }
        else{
            shoot_delay = 0.99;
            p1_shooting = false;
            if(p1_overheated == false) p1_overheat_lv-=0.15;
            if(p1_overheat_lv < 0) p1_overheat_lv = 0;
        }
        if( currentKeyState[ SDL_SCANCODE_KP_0 ] ){
            if(p2->alive == false && p2_overheated == false){
                p2_overheat_lv-=0.15;
                if(p1_overheat_lv < 0) p1_overheat_lv = 0;
            }
            p2_shooting = true;
            if(p2_overheated == false && p2->alive == true)
                p2_overheat_lv += 0.15;
            if(p2_overheat_lv >= 100){
                p2_overheat_lv = 100;
                p2_overheated = true;
            }
        }
        else{
            shoot_delay_2 = 0.99;
            p2_shooting = false;
            if(p2_overheated == false) p2_overheat_lv-=0.15;
            if(p2_overheat_lv < 0) p2_overheat_lv = 0;
        }
        if( currentKeyState_2[ SDL_SCANCODE_UP ] ){
            Ship_Pos_2.y -= p2->move_speed;
            if(Ship_Pos_2.y < 0) Ship_Pos_2.y = 0;
        }
        if( currentKeyState_2[ SDL_SCANCODE_DOWN ] ){
            Ship_Pos_2.y += p2->move_speed;
            if(Ship_Pos_2.y > 750) Ship_Pos_2.y = 750;
        }
        if( currentKeyState_2[ SDL_SCANCODE_LEFT ] ){
            Ship_Pos_2.x -= p2->move_speed;
            if(Ship_Pos_2.x < 0) Ship_Pos_2.x = 0;
        }
        if( currentKeyState_2[ SDL_SCANCODE_RIGHT ] ){
            Ship_Pos_2.x += p2->move_speed;
            if(Ship_Pos_2.x > 1150) Ship_Pos_2.x = 1150;
        }
        if( currentKeyState_2[ SDL_SCANCODE_ESCAPE ] ){
            //if(e.key.keysym.sym == SDLK_q) game_over = true;
            game_paused = true;
        }
        while(SDL_PollEvent( &e ) != 0){
            if(e.type == SDL_QUIT){
                entities.clear();
                return 0;
            }
        }

        // ******************************************************************** //
        //// Check game pause /////
        if(game_paused == true){
            game_paused = false;
            int selection = Pause_Menu(&e);
            if(selection == 1){
                entities.clear();
                return Game_Play(duel_play);
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

        // *************************************************************** //
        // CHECK GAME OVER //
        if(p1_dead == true){
            if(duel_play == true){
                if(p2_dead == true) game_over = true;
            }
            else game_over = true;
        }

        // **************************************************************** //
        /////////////////// Fire bullet //////////////////////////////
        if(p->alive == true && p1_dead == false && p1_shooting == true && p1_overheated == false){

        shoot_speed = 0.25;
        shoot_delay += shoot_speed;
        if(shoot_delay > 1){
            shoot_delay = 0;
            // reset the shoot delay time to 0 and create a new bullet;
            bullet *bul = new bullet();
            switch(p->bullet_num){
                case 1:
                    bul->settings(sBullet, Ship_Pos.x + 7, Ship_Pos.y, 0, 7);
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
        if(p2->alive == true && p2_dead == false && duel_play == true &&
           p2_shooting == true && p2_overheated == false){

        shoot_speed_2 = 0.25;
        // if the player has fast shoot then the shooting speed is 1.2 else it is 0.2
        shoot_delay_2 += shoot_speed_2;
        if(shoot_delay_2 > 1){
            shoot_delay_2 = 0;
            // reset the shoot delay time to 0 and create a new bullet;
            bullet_2 *bul = new bullet_2();
            switch(p2->bullet_num){
                case 1:
                    bul->settings(sBullet_2, Ship_Pos_2.x + 7, Ship_Pos_2.y, 0, 7);
                    break;
                case 2:
                    bul->settings(sBullet_2, Ship_Pos_2.x - 3, Ship_Pos_2.y, 0, 17);
                    break;
                case 3:
                    bul->settings(sBullet_2, (float)Ship_Pos_2.x - 12.2, Ship_Pos_2.y, 0, 30);
                    break;
            }
            // Check the amount of bullets that the player shoots each time
            entities.push_back(bul);
            Play_Sound(Fire_sound, 0);
        }
        }

        // ******************************************************************* //
        // CHECK OVERHEAT //
        if(p1_overheated == true){
            p1_overheat_cooldown += 0.2;
            if(p1_overheat_cooldown >= 70){
                p1_overheat_cooldown = 0;
                p1_overheated = false;
            }
        }
        if(p2_overheated == true){
            p2_overheat_cooldown += 0.2;
            if(p2_overheat_cooldown >= 70){
                p2_overheat_cooldown = 0;
                p2_overheated = false;
            }
        }

        // ******************************************************************* //
        ////////////////////// Fast shoot ///////////////////////////////
        if(p->move_speed == 10 && p1_dead == false){
            fast_shoot_time += delay_speed;
            // if the player has fast shoot then start the time delay for fast shooting
            if(fast_shoot_time > 150){
                fast_shoot_time = 0;
                p->move_speed = 6;
            }
            // When the delay is over reset to normal speed shooting
        }
        if(p2->move_speed == 10 && p2_dead == false){
            fast_shoot_time_2 += delay_speed;
            // if the player has fast shoot then start the time delay for fast shooting
            if(fast_shoot_time_2 > 150){
                fast_shoot_time_2 = 0;
                p2->move_speed = 6;
            }
            // When the delay is over reset to normal speed shooting
        }

        // ******************************************************************** //
        //////////////// Player respawn /////////////////////
        if(p->alive == false && p1_dead == false){  // When the player just die
            p->vulnerable = false;
            // The player will not be vulnerable
            respawn_time += delay_speed;
            // Then start the time delay for respawning
            if(respawn_time > 50){
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
        if(p2->alive == false && p2_dead == false){  // When the player just die
            p2->vulnerable = false;
            // The player will not be vulnerable
            respawn_time_2 += delay_speed;
            // Then start the time delay for respawning
            if(respawn_time_2 > 50){
                respawn_time_2 = 0;
                p2->settings(sPlayer_respawn, Ship_Pos_2.x, Ship_Pos_2.y, 0, 15);
                p2->alive = true;
                // if the player respawns set the animation of respawning
                // and set him back to alive
            }
            else{
                if(p2->revive == true){
                    p2->revive = false;
                    p2->settings(sPlayer_dead, Ship_Pos_2.x, Ship_Pos_2.y, 0, 15);
                    // if the player has not respawned then set the animation to death
                    // We use the variable p->revive to make sure the function settings
                    // above happens just once
                }
            }
        }

        // ******************************************************************* //
        if(p->anim.isEnd() == true && p1_dead == false){
            p->settings(sPlayer, Ship_Pos.x, Ship_Pos.y, 0, 15);
            p->vulnerable = true;
            // The space_ship only has the animation of respawning so this means
            // when the animation of respawning is over we set the animation back
            // to normal and make it vulnerable
        }
        if(p2->anim.isEnd() == true && p2_dead == false){
            p2->settings(sPlayer, Ship_Pos_2.x, Ship_Pos_2.y, 0, 15);
            p2->vulnerable = true;
            // The space_ship only has the animation of respawning so this means
            // when the animation of respawning is over we set the animation back
            // to normal and make it vulnerable
        }

        Handle_Collision(game_over, duel_play);

        if(p1_dead == false){
            p->Get_Position(Ship_Pos.x, Ship_Pos.y);
            p1_id.Set_Position(Ship_Pos.x + 6, Ship_Pos.y + 35);
        }
        if(p2_dead == false){
            p2->Get_Position(Ship_Pos_2.x, Ship_Pos_2.y);
            p2_id.Set_Position(Ship_Pos_2.x + 6, Ship_Pos_2.y + 35);
        }
        // Set the position of the player according to the variable Ship_Pos

        for(auto a:entities){
            if(a->name == "explosion" || a->name == "ship_explosion"){
                if(a->anim.isEnd()) a->life = false;
            }
            // if the animation of exposions is over we destroy them so
            // that explosions only happen once
        }

        if (rand() % 100 < ((duel_play == true) ? 3 : 2))
        {
           asteroid *a = new asteroid();
           a->settings(sRock, rand() % 1150, 0, rand()%360, 25);
           entities.push_back(a);
        }
        // Randomly create a new asteroid

        if (rand() % ((duel_play == true) ? 2000 : 4000) < 2){
            package *bp = new package("bullet_pack");
            bp->settings(sBullet_pack, rand() % 1150, 0, 0, 35);
            entities.push_back(bp);
        }
        // Randomly create a new bullet package

        if (rand() % ((duel_play == true) ? 3000 : 5000) < 2){
            package *b = new package("bomb");
            b->settings(sBomb, rand() % 1150, 0, 0, 35);
            entities.push_back(b);
        }
        // Randomly create a new bomb package

        if (rand() % 3000 < ((duel_play == true) ? 4 : 2)){
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
        if(p->alive == true) p1_id.render();
        if(p2->alive == true && duel_play == true) p2_id.render();

        Life.render();
        Score_background.render();
        Score.render();
        score_amount.render();
        Overheat_frame_1.render();
        Overheat_1.Set_Rect(0, 0, 1200 * (int)p1_overheat_lv / 100, 70);
        Overheat_1.Set_Size(198 * (int)p1_overheat_lv / 100, 24);
        Overheat_1.render();
        if(duel_play == true){
            Life_2.render();
            Score_background_2.render();
            Score_2.render();
            score_amount_2.render();
            Overheat_frame_2.render();
            Overheat_2.Set_Rect(0, 0, 1200 * (int)p2_overheat_lv / 100, 70);
            Overheat_2.Set_Size(198 * (int)p2_overheat_lv / 100, 24);
            Overheat_2.render();
        }

        SDL_RenderPresent(gRenderer);
    }

    Update_High_Score(final_score_1);
    Update_High_Score(final_score_2);

    ////////////// Game over screen ////////////////////

    SDL_ShowCursor(SDL_ENABLE);

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
                return Game_Play(duel_play);
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

        //////////////// Draw ///////////////////////////
        for(auto i = entities.begin() ; i != entities.end() ; ){
            Entity *e = *i;

            if(e->name == "ship_explosion"){
                if(e->anim.isEnd()) e->life = false;
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
        Game_Over.render();
        Replay_but.render();
        Main_Menu_but.render();
        Exit_but.render();

        SDL_RenderPresent(gRenderer);
    }
}
