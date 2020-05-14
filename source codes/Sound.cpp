#include "Sound.h"

Mix_Chunk *Fire_sound = nullptr;
Mix_Chunk *explo_sound = nullptr;
Mix_Chunk *bonus_sound = nullptr;
Mix_Chunk *ship_explo = nullptr;

void Init_Sound(){
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 4, 256);
    Fire_sound = Mix_LoadWAV("sound/fire.wav");
    explo_sound = Mix_LoadWAV("sound/EXPLO CLASSIC.WAV");
    bonus_sound = Mix_LoadWAV("sound/bonus.mp3");
    ship_explo = Mix_LoadWAV("sound/ship explo.wav");
}

void Play_Sound(Mix_Chunk *sound, int channel){
    Mix_PlayChannel(channel, sound, 0);
}

void close_sound(){
    Mix_FreeChunk(Fire_sound);
    Fire_sound = nullptr;
    Mix_FreeChunk(explo_sound);
    explo_sound = nullptr;
    Mix_FreeChunk(bonus_sound);
    bonus_sound = nullptr;
    Mix_FreeChunk(ship_explo);
    ship_explo = nullptr;

    Mix_Quit();
}


