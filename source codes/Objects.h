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
    bool direction_up;
public:
    bullet(std::string name_, bool direction_up_);

    void update();
};

//////////////////////////////////////////

class player: public Entity
{
   public:

    int bullet_num = 1;
    int move_speed = 6;
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

///////////////////////////////////////////

class boss: public Entity{

    public:
        bool intro;
        bool special_attack;
        double spc_atk_charge;
        int max_health, current_health;

        boss(int max_health_, int move_speed_);

        void update();
};

#endif // OBJECTS_H_INCLUDED
