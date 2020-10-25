#pragma once
#include <curses.h>

#define PLAYFIELD_Y 20
#define PLAYFIELD_X 10


void drawPlayfield();
void updatePlayfield();
void clearPlayfield();

extern char playfieldArr[PLAYFIELD_Y][PLAYFIELD_X];
