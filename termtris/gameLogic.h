#pragma once

#include <conio.h>
#include <curses.h>
#include <cstdlib>
#include <chrono>

#include "win.h"


#define KEY_ESC		0x01b
#define KEY_C		0x63
#define KEY_Z		0x7a
#define KEY_SPACE	0x20 

using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;

struct piece
{
private:

	steady_clock::time_point lastLock;
	steady_clock::time_point lastFall;

	int shape = 0;

public:

	int rotation = 0;
	int	y = 0;
	int x = 0;

	bool shouldLock = false;

	void updateLastLock() 
	{
		lastLock = steady_clock::now();
		return;
	}
	
	void updateLastFall() 
	{
		lastFall = steady_clock::now();
		return;
	}

	void setShape(int newShape)
	{
		shape = newShape;
		return;
	}


	steady_clock::time_point getLastLock()
	{
		return lastLock;
	}

	steady_clock::time_point getLastFall()
	{
		return lastFall;
	}

	int getShape()
	{
		return shape;
	}

	void newPiece()
	{
		y = -1;
		x = 3;
		rotation = 0;

		srand(time(0));

		shape = rand() % 7;

		return;
	}

};

enum direction
{
	down,
	left,
	right
};

void drawPlayfield(win*[2]);
void updatePlayfield(win*);
void clearPlayfield();
bool canMove(piece*, direction);
bool canRotate(piece*, direction);
void clearPiece(piece*);
void clearLines(int);
void block(piece*);


