#include <conio.h>
#include <time.h>
#include "header.h"


#define KEY_ESC 0x01b
#define KEY_C	0x63
#define KEY_Z	0x7a

time_t lastFall, now;
piece tetromino;

enum direction 
{
	down,
	left,
	right
};

bool canFit(piece, direction);

void logic() 
{
	int input;
	if (_kbhit())
	{
		input  = getch();
	}
	else
	{
		return;
	}
	
	switch (input)
	{
	case KEY_LEFT:
		clearPiece(tetromino);

		if (tetromino.x > 0)
		{
			tetromino.x--;
		}

		block(tetromino);

		break;
	case KEY_RIGHT:
		clearPiece(tetromino);

		if (tetromino.x < PLAYFIELD_X - 4)
		{
			tetromino.x++;
		}

		block(tetromino);
		break;
	case KEY_DOWN:
		clearPiece(tetromino);
	
		if (tetromino.y < PLAYFIELD_Y - 4)
		{
			tetromino.y++;
		}
	
		block(tetromino);
	
		break;
	case KEY_C:
		clearPiece(tetromino);

		if (tetromino.rotation > 0)
		{
			tetromino.rotation--;
		}
		else
		{
			tetromino.rotation = 3;
		}
		block(tetromino);
		break;
	case KEY_Z:
		clearPiece(tetromino);

		if (tetromino.rotation < 3)
		{
			tetromino.rotation++;
		}
		else
		{
			tetromino.rotation = 0;
		}
		block(tetromino);
		break;
	case KEY_ESC:
		
		isPlay = FALSE;

		break;
	default:
		break;
	}


}

void fall() 
{
	time(&now);
	if (difftime(now, lastFall) == 1 && tetromino.y < PLAYFIELD_Y - 4)
	{
		clearPiece(tetromino);

		tetromino.y++;

		block(tetromino);
		
		lastFall = now;
	}

	return;
}

bool canFit(piece tetromino, direction dir) 
{
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++)
			if ()
				return false;

	return true;
}

void startGame() 
{
	block(tetromino);
	drawPlayfield();
	return;
}