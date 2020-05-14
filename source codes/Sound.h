#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include <SDL_mixer.h>

void Init_Sound();

void Play_Sound(Mix_Chunk *sound, int channel);

void close_sound();

#endif // SOUND_H_INCLUDED
