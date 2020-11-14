#include "gameLogic.h"
#include "shapes.cpp"


using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;


void input(piece *tetromino, bool *isPlay)
{

	int input = 0;
	if (_kbhit())
	{
		input = getch();
	}
	
	switch (input)
	{
	case KEY_LEFT:
		if (canMove(*tetromino, left))
		{
			tetromino->x--;
		}
		break;
	case KEY_RIGHT:
		if (canMove(*tetromino, right))
		{
			tetromino->x++;
		}
		break;
	case KEY_DOWN:
		if (canMove(*tetromino, down))
		{
			tetromino->y++;
		}
		break;
	case KEY_C:
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
		break;
	case KEY_Z:
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
		break;
	case KEY_ESC:
		*isPlay = false;
		break;
	default:
		break;
	}
	return;
}

void fall(piece* tetromino, steady_clock::time_point *fall)
{
	duration<float, milli> diffTime = steady_clock::now() - *fall;
	if (diffTime >= 1000ms && canMove(*tetromino, down))
	{
		tetromino->y++;

		*fall = steady_clock::now();
		return;
	}
	return;
}

void lock(piece *tetromino, steady_clock::time_point *lastPlace, bool *shouldLock) //this function locks the piece 
{
	duration<float, milli> diffTime = steady_clock::now() - *lastPlace;

	if (*shouldLock && diffTime >= 250ms)
	{
		block(tetromino);

		clearLines(tetromino->y);

		newPiece(&*tetromino);
		*shouldLock = false;
		*lastPlace = steady_clock::now();
	}
	else
	{
		if (!canMove(*tetromino, down))
		{
			*shouldLock = true;
		}
		else
		{
			*lastPlace = steady_clock::now();
		}
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
				if (shapeArr[tetromino.shape][tetromino.rotation][y][x] == '#' && ( tetromino.x + x == 0 || playfieldArr[tetromino.y + y][tetromino.x + x - 1] == '#' ) )
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
				if (shapeArr[tetromino.shape][tetromino.rotation][y][x] == '#' && (tetromino.x + x + 1 == playfieldX || playfieldArr[tetromino.y + y][tetromino.x + x + 1] == '#' ) )
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
				if (shapeArr[tetromino.shape][tetromino.rotation][y][x] == '#' && (tetromino.y + y + 1 == playfieldY || playfieldArr[tetromino.y + y + 1][tetromino.x + x] == '#' ) )
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
					if (shapeArr[tetromino.shape][tetromino.rotation + 1][y][x] == '#' && (tetromino.x + x + 1 == 0 || tetromino.x + x == playfieldX || tetromino.y + y == playfieldY || playfieldArr[tetromino.y + y][tetromino.x + x] == '#' ) )
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
					if (shapeArr[tetromino.shape][0][y][x] == '#' && (tetromino.x + x + 1 == 0 || tetromino.x + x == playfieldX || tetromino.y + y == playfieldY ||  playfieldArr[tetromino.y + y][tetromino.x + x] == '#' ) )
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
					if (shapeArr[tetromino.shape][tetromino.rotation - 1][y][x] == '#' && (tetromino.x + x + 1 == 0 || tetromino.y + y == playfieldY || tetromino.x + x == playfieldX || playfieldArr[tetromino.y + y][tetromino.x + x] == '#' ) )
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
					if (shapeArr[tetromino.shape][3][y][x] == '#' && (tetromino.x + x + 1 == 0 || tetromino.y + y == playfieldY || tetromino.x + x == playfieldX || playfieldArr[tetromino.y + y][tetromino.x + x] == '#' ) )
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
	
	piece *tetromino = new piece;
	
	tetromino->y = -1;
	tetromino->x = 3;
	tetromino->rotation = 0;
	
	newPiece(tetromino);
	block(tetromino);
	drawPlayfield();
	
	bool *shouldLock = new bool;
	bool *isPlay = new bool;

	*shouldLock = false;
	*isPlay = true;

	steady_clock::time_point *lastLock		= new steady_clock::time_point;
	steady_clock::time_point *lastFall		= new steady_clock::time_point;
	
	*lastLock = steady_clock::now();
	*lastFall  = steady_clock::now();

	while (*isPlay) //main game loop
	{
		clearPiece(*tetromino);

		input(tetromino, isPlay);
		
		fall(tetromino, lastFall);
		
		lock(tetromino, lastLock, shouldLock);

		block(tetromino);

		updatePlayfield();
	}

	delete tetromino;

	delete lastFall;
	delete lastLock;

	delete shouldLock;
	delete isPlay;

	return;
}

void clearPlayfield() //this function is used to clear the whole playfield
{
	for (int y = 0; y < playfieldY; y++)
	{
		for (int x = 0; x < playfieldX; x++)
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

void block(piece *tetromino) //this function puts the piece in playfieldArr
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (shapeArr[tetromino->shape][tetromino->rotation][y][x] == '#')
			{
				playfieldArr[tetromino->y + y][tetromino->x + x] = shapeArr[tetromino->shape][tetromino->rotation][y][x];
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
			for (int x = 0; x < playfieldX; x++)
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