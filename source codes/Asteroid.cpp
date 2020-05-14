#include "Asteroid.h"

asteroid::asteroid(){
    dx = rand() % 5 - 2;
    dy = rand() % 5 + 1;
    dy /= 3.0;
    // Divide dy for 3.0 so that the asteroids would not move too fast
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
