#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include <SDL.h>
#include<iostream>
#include<list>
#include<fstream>
#include<algorithm>

using namespace std;

int Main_Menu();

int Pause_Menu(SDL_Event *e);

int Display_High_Scores();

void Update_High_Score(int score);

#endif // MAINMENU_H_INCLUDED
