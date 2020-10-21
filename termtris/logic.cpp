#include <conio.h>
#include <time.h>
#include "header.h"
#include "shapes.cpp"

#define KEY_ESC		0x01b
#define KEY_C		0x63
#define KEY_Z		0x7a
#define KEY_SPACE	0x20 

struct piece
{
	int shape = 0, rotation = 0, y = 0, x = 0;
};

time_t lastFall, now;
piece tetromino;
bool isPlay;

enum direction 
{
	down,
	left,
	right
};


bool canMove(piece, direction);
bool canRotate(piece, direction);
void clearPiece(piece);
void block(piece);

void logic()
{
	int input = 0;
	if (_kbhit())
		input = getch();
	
	switch (input)
	{
	case KEY_LEFT:
		clearPiece(tetromino);

		if (canMove(tetromino, left))
			tetromino.x--;

		block(tetromino);
		break;
	case KEY_RIGHT:
		clearPiece(tetromino);

		if (canMove(tetromino, right))
			tetromino.x++;

		block(tetromino);
		break;
	case KEY_DOWN:
		clearPiece(tetromino);

		if (canMove(tetromino, down))
			tetromino.y++;

		block(tetromino);
		break;
	case KEY_C:
		clearPiece(tetromino);
		if (canRotate(tetromino, right))
		{
			if (tetromino.rotation > 0)
				tetromino.rotation--;
			else
				tetromino.rotation = 3;
		}
		block(tetromino);
		break;
	case KEY_Z:
		clearPiece(tetromino);

		if (canRotate(tetromino, left))
		{
			if (tetromino.rotation < 3)
				tetromino.rotation++;
			else
				tetromino.rotation = 0;
		}
		block(tetromino);
		break;
	//case KEY_SPACE:
	//	for(int y = 0;)
	//		for(int x = 0; x < 4; x++)
	//			
	//	break;
	case KEY_ESC:
		isPlay = FALSE;
		break;
	default:
		break;
	}



	return;
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

bool canMove(piece tetromino, direction dir) //this function checks if you can move a piece in a specified direction
{
	switch (dir) 
	{
	case left:
		for (int y = 0; y < 4; y++)
			for (int x = 0; x < 4; x++)
				if (shapeArr[tetromino.shape][tetromino.rotation][y][x] == 'o' && tetromino.x  + x == 0 || shapeArr[tetromino.shape][tetromino.rotation][y][x] == 'o' && playfieldArr[tetromino.y + y][tetromino.x + x - 1] == 'o')
					return false;
		return true;
		break;
	case right:
		for (int y = 0; y < 4; y++)
			for (int x = 0; x < 4; x++)
				if (shapeArr[tetromino.shape][tetromino.rotation][y][x] == 'o' && tetromino.x + x + 1== PLAYFIELD_X|| shapeArr[tetromino.shape][tetromino.rotation][y][x] == 'o' && playfieldArr[tetromino.y + y][tetromino.x + x + 1] == 'o')
					return false;
		return true;
		break;
	case down:
		for (int y = 0; y < 4; y++)
			for (int x = 0; x < 4; x++)
				if (shapeArr[tetromino.shape][tetromino.rotation][y][x] == 'o' && tetromino.y + y + 1 == PLAYFIELD_Y || shapeArr[tetromino.shape][tetromino.rotation][y][x] == 'o' && playfieldArr[tetromino.y + y + 1][tetromino.x + x] == 'o')
					return false;
		return true;
		break;
	default:
		return false;
		break;
	}
	
}

bool canRotate(piece tetromino, direction rotation)
{
	switch (rotation)
	{
	case left:
		if (tetromino.rotation < 3)
		{
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					if (shapeArr[tetromino.shape][tetromino.rotation + 1][y][x] == 'o' && (tetromino.x + x + 1 == 0 || tetromino.x + x == PLAYFIELD_X || tetromino.y + y == PLAYFIELD_Y) || shapeArr[tetromino.shape][tetromino.rotation + 1][y][x] == 'o' && playfieldArr[tetromino.y + y][tetromino.x + x] == 'o')
					{
						return false;
					}
				}
			}
		}
		else 
		{
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					if (shapeArr[tetromino.shape][0][y][x] == 'o' && (tetromino.x + x + 1 == 0 || tetromino.x + x == PLAYFIELD_X || tetromino.y + y == PLAYFIELD_Y) || shapeArr[tetromino.shape][0][y][x] == 'o' && playfieldArr[tetromino.y + y][tetromino.x + x] == 'o')
					{
						return false;
					}
				}
			}
		}
		return true;
		break;
	case right:
		if (tetromino.rotation > 0)
		{
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					if (shapeArr[tetromino.shape][tetromino.rotation - 1][y][x] == 'o' && (tetromino.x + x == PLAYFIELD_X || tetromino.x + x + 1 == 0 || tetromino.y + y == PLAYFIELD_Y) || shapeArr[tetromino.shape][tetromino.rotation - 1][y][x] == 'o' && playfieldArr[tetromino.y + y][tetromino.x + x] == 'o')
					{
						return false;
					}
				}
			}
		}
		else
		{
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					if (shapeArr[tetromino.shape][3][y][x] == 'o' && (tetromino.x + x == PLAYFIELD_X || tetromino.x + x + 1 == 0 || tetromino.y + y == PLAYFIELD_Y ) || shapeArr[tetromino.shape][3][y][x] == 'o' && playfieldArr[tetromino.y + y][tetromino.x + x] == 'o')
					{
						return false;
					}
				}
			}
		}
		return true;
		break;
	default:
		return false;
		break;
	}
}

void startGame() 
{
	tetromino.y = -1;
	tetromino.x = 3;
	tetromino.shape = 6;
	block(tetromino);
	drawPlayfield();
	time(&lastFall);
	isPlay = TRUE;

	while (isPlay)
	{

		logic();
		//fall();

		updatePlayfield();
	}
	return;
}

void clearPlayfield() //this function is used to clear the playfield
{
	for (int y = 0; y < PLAYFIELD_Y; y++)
	{
		for (int x = 0; x < PLAYFIELD_X; x++)
			playfieldArr[y][x] = ' ';
	}
}

void clearPiece(piece tetromino)
{
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++)
			if (shapeArr[tetromino.shape][tetromino.rotation][y][x] == 'o')
				playfieldArr[tetromino.y + y][tetromino.x + x] = ' ';
}

void block(piece tetromino)
{
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++)
			if (shapeArr[tetromino.shape][tetromino.rotation][y][x] == 'o')
				playfieldArr[tetromino.y + y][tetromino.x + x] = shapeArr[tetromino.shape][tetromino.rotation][y][x];
}