#pragma once
#include <curses.h>

#define PLAYFIELD_Y 20
#define PLAYFIELD_X 10

void checkWindow();
void drawPlayfield();
void updatePlayfield();
void clearPlayfield();
void initColour();
void logic();
void fall();
void startGame();

extern bool isPlay;
extern char playfieldArr[PLAYFIELD_Y][PLAYFIELD_X];
