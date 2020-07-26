#include "Objects.h"

/////////////// class asteroid //////////////////

asteroid::asteroid(){
    dx = rand() % 7 - 3;
    dy = rand() % 4 + 3;
    //dy /= 2.0;
    // Divide dy for 4.0 so that the asteroids would not move too fast
    // The speed can be 1, 1.25, 1.5, 1.75, 2
    name = "asteroid";
}

void asteroid::update(){
    x += dx;
    y += dy;
    if(x > 1150) dx = -dx;
    if(x < 0) dx = -dx;
    // The asteroid would bounce back if it touches the left and right edges
    if(y > 800) y = 0;
    if(y < 0) y = 800;
    // and it will reappear on the opposite side it it touches the up and down edge
}

asteroid_small::asteroid_small(){
    dx = rand() % 7 - 3;
    dy = rand() % 4 + 3;
    //dy /= 2.0;
    // Divide dy for 4.0 so that the asteroids would not move too fast
    // The speed can be 1, 1.25, 1.5, 1.75, 2
    name = "asteroid_small";
}

void asteroid_small::update(){
    x += dx;
    y += dy;
    if(x > 1150) dx = -dx;
    if(x < 0) dx = -dx;
    // The asteroid would bounce back if it touches the left and right edges
    if(y > 800) y = 0;
    if(y < 0) y = 800;
    // and it will reappear on the opposite side it it touches the up and down edge
}

//////////////// class bullet ///////////////////////

bullet::bullet(std::string name_, bool direction_up_){
    name = name_;
    direction_up = direction_up_;
}

void bullet::update(){
    y -= ((direction_up == true) ? 14 : -9);
    if(y < 0 || y > 800) life = false;
    // if the bullet flies above the screen it will be destroyed
}

//////////////// class player //////////////////////////

player::player(){
    name="player";
    scores = 0;
}

void player::Get_Position(int x_, int y_){
    x = x_;
    y = y_;
}

void player::reset(){
    bullet_num = 1;
    move_speed = 6;
}

//////////////// class package ////////////////////////////

package::package(std::string name_){
    name = name_;
}

void package::update(){
    y += 4;
    if(y > 800) life = false;
    // if the package falls below the screen it will be destroyed
}

////////////////// class boss //////////////////////////////

boss::boss(int max_health_, int move_speed_){
    max_health = max_health_;
    current_health = max_health;
    dx = move_speed_;
    special_attack = false;
    spc_atk_charge = 0;
    dy = 13;
    intro = true;
}

void boss::update(){
    if(intro == true){
        y += 1;
        if(y > 20){
            y = 20;
            intro = false;
        }
    }
    else if(special_attack == false){
        x += dx;
        if(x < 0 || x > 1200-anim.t.on_Screen.w) dx = -dx;
        if(rand() % 200 == 0) dx = -dx;
        if(rand() % 300 == 0) special_attack = true;
    }
    else{
        spc_atk_charge += 0.2;
        if(spc_atk_charge > 12){
            y+=dy;
            if(y > 800 - anim.t.on_Screen.h){
                dy = -dy;
            }
            if(y < 20){
                y = 20;
                dy = -dy;
                special_attack = false;
                spc_atk_charge = 0;
            }
        }
    }
}
