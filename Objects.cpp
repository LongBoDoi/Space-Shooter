#include "Objects.h"

/////////////// class asteroid //////////////////

asteroid::asteroid(){
    dx = rand() % 5 - 2;
    dy = rand() % 5 + 1;
    dy /= 4.0;
    if(dy < 1) dy = 1;
    // Divide dy for 4.0 so that the asteroids would not move too fast
    // The minimum speed is 1 however
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

//////////////// class bullet ///////////////////////

bullet::bullet(){
    name = "bullet";
}

void bullet::update(){
    y -= 5;
    if(y < 0) life = false;
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
    fast_shoot_enabled = false;
}

//////////////// class package ////////////////////////////

package::package(std::string name_){
    name = name_;
}

void package::update(){
    y += 2;
    if(y > 800) life = false;
    // if the package falls below the screen it will be destroyed
}
