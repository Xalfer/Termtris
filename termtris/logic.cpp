#include <conio.h>
#include <cstdlib>
#include <chrono>
#include "header.h"
#include "shapes.cpp"

#define KEY_ESC		0x01b
#define KEY_C		0x63
#define KEY_Z		0x7a
#define KEY_SPACE	0x20 

using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;


bool isPlay, isBlock;
struct piece
{
	int shape = 0, rotation = 0, y = 0, x = 0;
};

enum direction 
{
	down,
	left,
	right
};

steady_clock::time_point lastFall, shouldPlace, now;



bool canMove(piece, direction);
bool canRotate(piece, direction);
void clearPiece(piece);
void clearLines(int);
void block(piece);
void newPiece(piece*);

void logic(piece *tetromino)
{

	int input = 0;
	if (_kbhit())
	{
		input = getch();
	}
	
	switch (input)
	{
	case KEY_LEFT:
		clearPiece(*tetromino);

		if (canMove(*tetromino, left))
		{
			tetromino->x--;
		}

		block(*tetromino);
		break;
	case KEY_RIGHT:
		clearPiece(*tetromino);

		if (canMove(*tetromino, right))
		{
			tetromino->x++;
		}

		block(*tetromino);
		break;
	case KEY_DOWN:
		clearPiece(*tetromino);

		if (canMove(*tetromino, down))
		{
			tetromino->y++;
		}

		block(*tetromino);
		break;
	case KEY_C:
		clearPiece(*tetromino);
		if (canRotate(*tetromino, right))
		{
			if (tetromino->rotation > 0)
			{
				tetromino->rotation--;
			}
			else
			{
				tetromino->rotation = 3;
			}
		}
		block(*tetromino);
		break;
	case KEY_Z:
		clearPiece(*tetromino);

		if (canRotate(*tetromino, left))
		{
			if (tetromino->rotation < 3)
			{
				tetromino->rotation++;
			}
			else
			{
				tetromino->rotation = 0;
			}
		}
		block(*tetromino);
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

void fall(piece* tetromino) 
{
	clearPiece(*tetromino);
	
	now = steady_clock::now();
	duration<float, milli> diffTime = now - lastFall;
	if (diffTime >= 1000ms && canMove(*tetromino, down))
	{
		tetromino->y++;

		lastFall = steady_clock::now();
		return;
	}
	
	block(*tetromino);
	return;
}

void lock(piece *tetromino)
{
	now = steady_clock::now();
	duration<float, milli> diffTime = now - shouldPlace;
	if (isBlock && diffTime >= 250ms)
	{
		block(*tetromino);

		clearLines(tetromino->y);

		newPiece(&*tetromino);
		isBlock = false;

	}
	else
	{
		clearPiece(*tetromino);
		
		if (!canMove(*tetromino, down))
		{
			isBlock = true;
		}
		else
		{
			shouldPlace = steady_clock::now();
		}
		
		block(*tetromino);
	}
	return;
}

bool canMove(piece tetromino, direction dir) //this function checks if you can move a piece in a specified direction
{
	switch (dir) 
	{
	case left:
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				if (shapeArr[tetromino.shape][tetromino.rotation][y][x] == '#' && tetromino.x + x == 0 || shapeArr[tetromino.shape][tetromino.rotation][y][x] == '#' && playfieldArr[tetromino.y + y][tetromino.x + x - 1] == '#')
				{
					return false;
				}
			}
		}
		break;
	case right:
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				if (shapeArr[tetromino.shape][tetromino.rotation][y][x] == '#' && tetromino.x + x + 1 == PLAYFIELD_X || shapeArr[tetromino.shape][tetromino.rotation][y][x] == '#' && playfieldArr[tetromino.y + y][tetromino.x + x + 1] == '#')
				{
					return false;
				}
			}
		}
		break;
	case down:
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				if (shapeArr[tetromino.shape][tetromino.rotation][y][x] == '#' && tetromino.y + y + 1 == PLAYFIELD_Y || shapeArr[tetromino.shape][tetromino.rotation][y][x] == '#' && playfieldArr[tetromino.y + y + 1][tetromino.x + x] == '#')
				{
					return false;
				}
			}
		}
		break;
	default:
		return false;
		break;
	}
	return true;
}

bool canRotate(piece tetromino, direction rotation) //this function checks if you can rotate the piece in a specified direction
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
					if (shapeArr[tetromino.shape][tetromino.rotation + 1][y][x] == '#' && (tetromino.x + x + 1 == 0 || tetromino.x + x == PLAYFIELD_X || tetromino.y + y == PLAYFIELD_Y) || shapeArr[tetromino.shape][tetromino.rotation + 1][y][x] == '#' && playfieldArr[tetromino.y + y][tetromino.x + x] == '#')
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
					if (shapeArr[tetromino.shape][0][y][x] == '#' && (tetromino.x + x + 1 == 0 || tetromino.x + x == PLAYFIELD_X || tetromino.y + y == PLAYFIELD_Y) || shapeArr[tetromino.shape][0][y][x] == '#' && playfieldArr[tetromino.y + y][tetromino.x + x] == '#')
					{
						return false;
					}
				}
			}
		}
		break;
	case right:
		if (tetromino.rotation > 0)
		{
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					if (shapeArr[tetromino.shape][tetromino.rotation - 1][y][x] == '#' && (tetromino.x + x + 1 == 0 || tetromino.y + y == PLAYFIELD_Y || tetromino.x + x == PLAYFIELD_X) || shapeArr[tetromino.shape][tetromino.rotation - 1][y][x] == '#' && playfieldArr[tetromino.y + y][tetromino.x + x] == '#')
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
					if (shapeArr[tetromino.shape][3][y][x] == '#' && (tetromino.x + x + 1 == 0 || tetromino.y + y == PLAYFIELD_Y || tetromino.x + x == PLAYFIELD_X) || shapeArr[tetromino.shape][3][y][x] == '#' && playfieldArr[tetromino.y + y][tetromino.x + x] == '#')
					{
						return false;
					}
				}
			}
			
		}
		break;
	default:
		return false;
		break;
	}
	return true;
}

void startGame() 
{
	clearPlayfield();
	piece tetromino;
	tetromino.y = -1;
	tetromino.x = 3;
	tetromino.rotation = 0;
	newPiece(&tetromino);
	block(tetromino);
	drawPlayfield();
	lastFall =	steady_clock::now();
	now =		steady_clock::now();
	isPlay = TRUE;
	while (isPlay)
	{
		fall(&tetromino);
		logic(&tetromino);
		lock(&tetromino);

		updatePlayfield();
	}
	return;
}

void clearPlayfield() //this function is used to clear the playfield
{
	for (int y = 0; y < PLAYFIELD_Y; y++)
	{
		for (int x = 0; x < PLAYFIELD_X; x++)
		{
			playfieldArr[y][x] = ' ';
		}
	}
}

void clearPiece(piece tetromino)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (shapeArr[tetromino.shape][tetromino.rotation][y][x] == '#')
			{
				playfieldArr[tetromino.y + y][tetromino.x + x] = ' ';
			}
		}
	}
}

void block(piece tetromino)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (shapeArr[tetromino.shape][tetromino.rotation][y][x] == '#')
			{
				playfieldArr[tetromino.y + y][tetromino.x + x] = shapeArr[tetromino.shape][tetromino.rotation][y][x];
			}
		}
	}
}

void newPiece(piece *tetromino)
{
	tetromino->y = -1;
	tetromino->x = 3;
	tetromino->rotation = 0;
	srand(time(0));

	tetromino->shape = rand() % 7;

	return;
}

void clearLines(int tetrominoY)
{
	for (int y = 0; y < 4; y++)
	{
		if (playfieldArr[tetrominoY + y][0] == '#' && playfieldArr[tetrominoY + y][1] == '#' && playfieldArr[tetrominoY + y][2] == '#' && playfieldArr[tetrominoY + y][3] == '#' && playfieldArr[tetrominoY + y][4] == '#' && playfieldArr[tetrominoY + y][5] == '#' && playfieldArr[tetrominoY + y][6] == '#' && playfieldArr[tetrominoY + y][7] == '#' && playfieldArr[tetrominoY + y][8] == '#' && playfieldArr[tetrominoY + y][9] == '#')
		{
			for (int x = 0; x < PLAYFIELD_X; x++)
			{
				playfieldArr[tetrominoY + y][x] = ' ';
				for (int i = tetrominoY + y; i > 0; i--)
				{
					playfieldArr[i][x] = playfieldArr[i - 1][x];
				}
			}
		}
	}
}