#include "Animation.h"

extern Texture Space_Ship, gBackGround, Explosion, Rock, small_rock, Bullet,
        Bullet_pack, Ship_Explosion, Bomb, Fast_shoot, Life, Score_background,
        Bullet_2;

animation sBullet, sExplosion, ship_explosion, sPlayer, sPlayer_dead, sPlayer_respawn,
            sBullet_pack, sBomb, sFast_shoot, sRock, sRock_small, sBullet_2;

animation::animation(Texture t_, int x, int y, int w, int h, int Count, float Speed){
    free();
    Frame = 0;
    speed = Speed;

    for(int i = 0 ; i < Count ; i++){
        SDL_Rect rect = {x + i * w, y , w, h};
        frames.push_back(rect);
    }

    t = t_;
    t.Set_Size(w, h);
    t.Set_Rect(frames[0].x, frames[0].y, frames[0].w, frames[0].h);
}

void animation::Update(){
    Frame += speed;
    int n = frames.size();
    if(Frame >= n) Frame -= n;
    if(n > 0) t.Set_Rect(frames[int(Frame)].x, frames[int(Frame)].y,
                         frames[int(Frame)].w, frames[int(Frame)].h);
}

void animation::free(){
    Frame = 0;  speed = 0;
    frames.clear();
}

bool animation::isEnd(){
    return Frame+speed>=frames.size();
}

/////////////////////////////////////////////////

void Init_Animation(){
    sBullet = animation(Bullet, 0, 0, 32, 64, 16, 0.8);
    sBullet_2 = animation(Bullet_2, 0, 0, 32, 64, 16, 0.8);
    sExplosion = animation(Explosion, 0, 0, 256, 256, 48, 0.65);
    ship_explosion = animation(Ship_Explosion, 0, 0, 192, 192, 64, 0.65);
    sPlayer = animation(Space_Ship, 39, 0, 39, 39, 1, 0);
    sPlayer_dead = animation(Space_Ship, 0, 0, 39, 39, 1, 0);
    sPlayer_respawn = animation(Space_Ship, 78, 0, 39, 39, 29, 0.2);
    sBullet_pack = animation(Bullet_pack, 0, 0, 1000, 1000, 1, 0);
    sBomb = animation(Bomb, 0, 0, 200, 200, 1, 0);
    sFast_shoot = animation(Fast_shoot, 0, 0, 1000, 1000, 1, 0);
    sBullet_pack.t.Set_Size(50, 50);
    sBomb.t.Set_Size(50, 50);
    sFast_shoot.t.Set_Size(50, 50);
    sRock = animation(Rock, 0, 0, 48, 48, 16, 0.6);
    sRock_small = animation(small_rock, 0, 0, 64, 64, 16, 0.6);
}
