#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include <SDL.h>
#include<iostream>
#include<list>
#include<fstream>
#include<algorithm>

using namespace std;

int Main_Menu();

int Play_Mode_Menu();

int Pause_Menu(SDL_Event *e, bool duel_play);

int Display_High_Scores();

void Update_High_Score(int score);

#endif // MAINMENU_H_INCLUDED
