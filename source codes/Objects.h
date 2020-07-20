#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED

#include "Entity.h"

class asteroid: public Entity
{
    // Asteroid is one of the objects that comes in large quantities so
    // we link this class with the class Entity
    public:
        asteroid();

        void update();
};

class asteroid_small: public Entity
{
    // Asteroid is one of the objects that comes in large quantities so
    // we link this class with the class Entity
    public:
        asteroid_small();

        void update();
};

//////////////////////////////////////

class bullet: public Entity{
public:
    bullet();

    void update();
};

class bullet_2: public Entity{
public:
    bullet_2();

    void update();
};

//////////////////////////////////////////

class player: public Entity
{
   public:

    int bullet_num = 1;
    bool fast_shoot_enabled = false;
    bool alive = true;
    bool vulnerable = true;
    bool revive = false;
    int lifes = 3;
    int scores;

   player();

   void Get_Position(int x_, int y_);

   void reset();
   // reset after the player dies

   void update(){}
};

////////////////////////////////////////

class package: public Entity{
    // Used for different packages like extra_bullets, fast_shoot, bomb
    public:
        package(std::string name_);

        void update();
};

#endif // OBJECTS_H_INCLUDED
