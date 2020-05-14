#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include "Entity.h"

class asteroid: public Entity{
    // Asteroid is one of the objects that comes in large quantities so
    // we link this class with the class Entity
    public:
        asteroid();

        void update();
};

#endif // ASTEROID_H_INCLUDED
