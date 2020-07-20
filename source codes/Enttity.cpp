#include "Entity.h"
#include "Objects.h"
#include "Sound.h"

extern std::list<Entity*> entities;

extern animation sBullet, sExplosion, ship_explosion, sPlayer, sPlayer_dead, sPlayer_respawn,
            sBullet_pack, sBomb, sFast_shoot, sRock, sBullet_2, sRock_small;
extern Mix_Chunk *Fire_sound, *explo_sound, *bonus_sound, *ship_explo;


extern player *p, *p2;

extern Texture Space_Ship, gBackGround, Explosion, Rock, Bullet, Life_2,
        Bullet_pack, Ship_Explosion, Bomb, Fast_shoot, Life, Score_background;
extern Word_Texture Score, score_amount, score_amount_2;

extern SDL_Point Ship_Pos, Ship_Pos_2;

extern float fast_shoot_time, fast_shoot_time_2;

extern bool p1_dead, p2_dead;

extern int final_score_1, final_score_2;

Entity::Entity(){
    life = true;
}

void Entity::settings(animation &a, int X, int Y, double Angle, int radius){
    anim.free();
    x = X;
    y = Y;
    anim = a;
    angle = Angle;
    R = radius;
}

void Entity::draw(){
    anim.t.Set_Position(x, y);
    anim.t.Set_Rotation(angle);
    anim.t.render();
}

bool is_Collide(Entity *a, Entity *b){
    return sqrt(pow(b->x - a->x, 2) + pow(b->y - a->y, 2)) < a->R + b->R;
}

void Handle_Collision(bool& game_over, bool duel_play){
    for(auto a:entities){
        for(auto b:entities){
            if((a->name == "asteroid" || a->name == "asteroid_small") && b->name == "bullet"){
                if(is_Collide(b, a)){
                    // if an asteroid and a bullet collide
                    a->life = false;
                    b->life = false;
                    // Destroy both objects

                    Entity *e = new Entity();
                    e->settings(sExplosion,a->x - 97,a->y - 97);
                    e->name="explosion";
                    entities.push_back(e);
                    // Create an explosion Entity at the position where they met;

                    if(a->name == "asteroid"){
                    asteroid_small *a1 = new asteroid_small();
                    a1->settings(sRock_small, a->x, a->y, rand()%360, 13);
                    entities.push_back(a1);
                    asteroid_small *a2 = new asteroid_small();
                    a2->settings(sRock_small, a->x, a->y, rand()%360, 13);
                    entities.push_back(a2);
                    }
                    // Create 2 small rocks from the big rock that just exploded

                    p->scores += 10;
                    score_amount.Load_From_Number(p->scores);
                    // add the score of the player with 10 and update the Word_Texture score_amount

                    Play_Sound(explo_sound, 1);
                }
            }
            if((a->name == "asteroid" || a->name == "asteroid_small") && b->name == "bullet_2"){
                if(is_Collide(b, a)){
                    // if an asteroid and a bullet collide
                    a->life = false;
                    b->life = false;
                    // Destroy both objects

                    Entity *e = new Entity();
                    e->settings(sExplosion,a->x - 97,a->y - 97);
                    e->name="explosion";
                    entities.push_back(e);
                    // Create an explosion Entity at the position where they met;

                    if(a->name == "asteroid"){
                    asteroid_small *a1 = new asteroid_small();
                    a1->settings(sRock_small, a->x - 97, a->y - 97, rand()%360, 13);
                    entities.push_back(a1);
                    asteroid_small *a2 = new asteroid_small();
                    a2->settings(sRock_small, a->x - 97, a->y - 97, rand()%360, 13);
                    entities.push_back(a2);
                    }

                    p2->scores += 10;
                    score_amount_2.Load_From_Number(p2->scores);
                    // add the score of the player with 10 and update the Word_Texture score_amount

                    Play_Sound(explo_sound, 1);
                }
            }
        }
        // ***************************************************** //
        if((a->name == "asteroid" || a->name == "asteroid_small") && p->vulnerable == true && p1_dead == false){
            if(is_Collide(a, p)){
                final_score_1 = p->scores;
                // if the player and an asteroid collide
                a->life = false;
                // Destroy the asteroid
                p->alive = false;
                p->revive = true;
                // Set the player dead and start to respawn
                p->lifes--;
                // Decrease the player lifes for 1;
                p->scores -= 100;
                if(p->scores < 0) p->scores = 0;
                // Decrease the player score for 100 and make sure it is not negative
                p->reset();
                // reset the player

                Life.Set_Rect(0, p->lifes *64, 212, 64);
                score_amount.Load_From_Number(p->scores);
                sBullet = animation(Bullet, 0, 0, 32, 64, 16, 0.8);
                // Change the texture of the life bar, score_amount and the animation sBullet
                // as the number of bullets has reset

                Entity *e = new Entity();
                e->settings(ship_explosion,Ship_Pos.x - 65, Ship_Pos.y - 90);
                e->name="ship_explosion";
                entities.push_back(e);
                // Create a ship_explosion Entity at the position of the player

                if(p->lifes == 0){
                    p->life = false;
                    p1_dead = true;
                    // if the player lifes is 0 then destroy the player entity and quit the loop to
                    // come to the game_over screen
                }

                Play_Sound(ship_explo, 3);
            }
        }
        if((a->name == "asteroid" || a->name == "asteroid_small") &&
            p2->vulnerable == true && p2_dead == false && duel_play == true){
            if(is_Collide(a, p2)){
                final_score_2 = p2->scores;
                // if the player and an asteroid collide
                a->life = false;
                // Destroy the asteroid
                p2->alive = false;
                p2->revive = true;
                // Set the player dead and start to respawn
                p2->lifes--;
                // Decrease the player lifes for 1;
                p2->scores -= 100;
                if(p2->scores < 0) p2->scores = 0;
                // Decrease the player score for 100 and make sure it is not negative
                p2->reset();
                // reset the player

                Life_2.Set_Rect(0, p2->lifes * 64, 212, 64);
                score_amount_2.Load_From_Number(p2->scores);
                sBullet_2 = animation(Bullet, 0, 0, 32, 64, 16, 0.8);
                // Change the texture of the life bar, score_amount and the animation sBullet
                // as the number of bullets has reset

                Entity *e = new Entity();
                e->settings(ship_explosion,Ship_Pos_2.x - 65, Ship_Pos_2.y - 90);
                e->name="ship_explosion";
                entities.push_back(e);
                // Create a ship_explosion Entity at the position of the player

                if(p2->lifes == 0){
                    p2->life = false;
                    p2_dead = true;
                    // if the player lifes is 0 then destroy the player entity and quit the loop to
                    // come to the game_over screen
                }

                Play_Sound(ship_explo, 3);
            }
        }
        // ************************************************** //
        if(a->name == "bullet_pack" && p->alive == true && p1_dead == false){
            if(is_Collide(a, p)){
                Play_Sound(bonus_sound, 3);

                // if the player and the bullet package collide
                a->life = false;
                // Destroy the bullet package
                p->bullet_num++;
                // add 1 to the number of bullets
                p->scores += 50;
                score_amount.Load_From_Number(p->scores);
                // add 50 to the player score and update score_amount
                if(p->bullet_num > 3) p->bullet_num = 3;
                // the maximum of number of bullets is 3
                if(p->bullet_num == 2){
                    sBullet = animation(Bullet, 0, 64, 52, 64, 16, 0.8);
                }
                else if(p->bullet_num == 3){
                    sBullet = animation(Bullet, 0, 128, 70, 64, 16, 0.8);
                }
                // set the animation of bullet according to the number of bullet which has just been updated
            }
        }
        if(a->name == "bullet_pack" && p2->alive == true && p2_dead == false
           && duel_play == true){
            if(is_Collide(a, p2)){
                Play_Sound(bonus_sound, 3);

                // if the player and the bullet package collide
                a->life = false;
                // Destroy the bullet package
                p2->bullet_num++;
                // add 1 to the number of bullets
                p2->scores += 50;
                score_amount_2.Load_From_Number(p2->scores);
                // add 50 to the player score and update score_amount
                if(p2->bullet_num > 3) p2->bullet_num = 3;
                // the maximum of number of bullets is 3
                if(p2->bullet_num == 2){
                    sBullet_2 = animation(Bullet, 0, 64, 52, 64, 16, 0.8);
                }
                else if(p2->bullet_num == 3){
                    sBullet_2 = animation(Bullet, 0, 128, 70, 64, 16, 0.8);
                }
                // set the animation of bullet according to the number of bullet which has just been updated
            }
        }
        // ****************************************************** //
        if(a->name == "bomb" && p->alive == true && p1_dead == false){
            if(is_Collide(a, p)){
                Play_Sound(bonus_sound, 3);
                // if the player and the bomb package collide
                a->life = false;
                // Destroy the bomb package
                p->scores += 50;
                score_amount.Load_From_Number(p->scores);
                // add 50 to the player score and update score_amount
                for(auto a:entities){
                    if(a->name == "asteroid" || a->name == "asteroid_small"){
                        a->life = false;

                        Entity *e = new Entity();
                        e->settings(sExplosion,a->x - 97,a->y - 97);
                        e->name="explosion";
                        entities.push_back(e);

                        p->scores += 10;
                        score_amount.Load_From_Number(p->scores);
                    }

                    Play_Sound(explo_sound, rand() % 3);
                }
                // Destroy all the asteroids on the screen, create new explosions entities and add score
                // to the player score
            }
        }
        if(a->name == "bomb" && p2->alive == true && p2_dead == false
           && duel_play == true){
            if(is_Collide(a, p2)){
                Play_Sound(bonus_sound, 3);
                // if the player and the bomb package collide
                a->life = false;
                // Destroy the bomb package
                p2->scores += 50;
                score_amount_2.Load_From_Number(p2->scores);
                // add 50 to the player score and update score_amount
                for(auto a:entities){
                    if(a->name == "asteroid" || a->name == "asteroid_small"){
                        a->life = false;

                        Entity *e = new Entity();
                        e->settings(sExplosion,a->x - 97,a->y - 97);
                        e->name="explosion";
                        entities.push_back(e);

                        p2->scores += 10;
                        score_amount.Load_From_Number(p2->scores);
                    }

                    Play_Sound(explo_sound, rand() % 3);
                }
                // Destroy all the asteroids on the screen, create new explosions entities and add score
                // to the player score
            }
        }
        // ******************************************************** //
        if(a->name == "fast_shoot" && p->alive == true && p1_dead == false){
            if(is_Collide(a, p)){
                Play_Sound(bonus_sound, 3);
                // if the player and the fast_shoot package collide
                fast_shoot_time = 0;
                // reset the fast_shoot time to 0
                a->life = false;
                // Destroy the package
                p->fast_shoot_enabled = true;
                // Set the player to fast shoot
                p->scores += 50;
                score_amount.Load_From_Number(p->scores);
                // add score and update
            }
        }
        if(a->name == "fast_shoot" && p2->alive == true && p2_dead == false
           && duel_play == true){
            if(is_Collide(a, p2)){
                Play_Sound(bonus_sound, 3);
                // if the player and the fast_shoot package collide
                fast_shoot_time_2 = 0;
                // reset the fast_shoot time to 0
                a->life = false;
                // Destroy the package
                p2->fast_shoot_enabled = true;
                // Set the player to fast shoot
                p2->scores += 50;
                score_amount_2.Load_From_Number(p2->scores);
                // add score and update
            }
        }
    }
}
