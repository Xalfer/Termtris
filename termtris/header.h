#pragma once
#include <curses.h>

#define PLAYFIELD_Y 20
#define PLAYFIELD_X 10

class piece 
{
public:
	int shape = 0, rotation = 0, y = 0, x = 0;
};

void drawPlayfield();
void updatePlayfield();
void clearPlayfield();
void clearPiece(piece);
void block(piece);
void logic();
void fall();
void initColour();
void startGame();

extern bool isPlay;
extern time_t lastFall;


