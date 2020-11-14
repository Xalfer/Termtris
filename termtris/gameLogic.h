#pragma once

#include <conio.h>
#include <curses.h>
#include <cstdlib>
#include <chrono>

#define playfieldY 20
#define playfieldX 10

#define KEY_ESC		0x01b
#define KEY_C		0x63
#define KEY_Z		0x7a
#define KEY_SPACE	0x20 

struct piece
{
	int shape = 0;
	int rotation = 0;
	int	y = 0;
	int x = 0;
};

enum direction
{
	down,
	left,
	right
};

void drawPlayfield();
void updatePlayfield();
void clearPlayfield();
bool canMove(piece, direction);
bool canRotate(piece, direction);
void clearPiece(piece);
void clearLines(int);
void block(piece*);
void newPiece(piece*);

extern char playfieldArr[playfieldY][playfieldX];
