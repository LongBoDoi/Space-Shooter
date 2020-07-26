#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <iostream>
#include <list>
#include <cmath>
#include "Animation.h"
#include "Entity.h"

class Entity {
    // This class is used to store different objects which come in large quantities
    // like rocks, bullets, packages, ....
    public:
        float x, y, dx, dy, R;
        double angle;
        bool life;
        std::string name;
        animation anim;
        // x, y: Position of object
        // dx, dy: Change of direction
        // angle: for rotation
        // R: Radius
        // life = true means the object still exists, false means it has been destroyed

        Entity();

        void settings(animation &a, int X, int Y, double Angle = 0, int radius = 1);

        virtual void update(){}

        void draw();

        virtual ~Entity(){};
};

bool is_Collide(Entity *a, Entity *b);
// Check whether object a collides with object b

bool shooted(Entity *a);

void Handle_Collision(bool& game_over, bool duel_play);

#endif // ENTITY_H_INCLUDED
