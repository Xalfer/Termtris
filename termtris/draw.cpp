#include "header.h"
#include "shapes.cpp"

struct wins
{
	int height, width, pos_y, pos_x;

	WINDOW* win;
};

char playfieldArr[PLAYFIELD_Y][PLAYFIELD_X] = {};

wins playfield;


void drawPlayfield() //this function is used for resizing and drawing the windows
{
	border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

	wins border;


	//this handles resizing the border for the playfield
	border.height = LINES;
	
	while (border.height % PLAYFIELD_Y != 2)
	{
		border.height--;
	}

	border.width = (border.height / 2) + 1;


	border.pos_y = (LINES - border.height) / 2;
	border.pos_x = (COLS - border.width) / 2;


	border.win = newwin(border.height, border.width, border.pos_y, border.pos_x);

	box(border.win, 0, 0);


	//this makes the playfield window
	playfield.height = border.height - 2;
	playfield.width = border.width - 2;
	playfield.pos_y = border.pos_y + 1;
	playfield.pos_x = border.pos_x + 1;

	playfield.win = newwin(playfield.height, playfield.width, playfield.pos_y, playfield.pos_x);

	refresh();
	wrefresh(border.win);
	wrefresh(playfield.win);
}

void updatePlayfield() //this function is used for updating the playfield
{

	const int blockSize  = playfield.height / PLAYFIELD_Y;
	
	for (short y = 0; y < PLAYFIELD_Y * blockSize; y++) 
	{
		for (short x = 0; x < PLAYFIELD_X * blockSize; x++)
		{
			//attron(COLOR_PAIR(2));
			
			mvwprintw(playfield.win, y, x, "%c", playfieldArr[y / blockSize][x / blockSize]);
			
			//attroff(COLOR_PAIR(2));
		}
	}	
	wrefresh(playfield.win);
	refresh();
}

void checkWindow()
{
	if (LINES < 22 || COLS < 12)
	{
		mvprintw(LINES / 2, (COLS - 24) / 2, "your window is too small");
		endwin();
		return;
	}
	return;
}

void clearLines(int tetrominoY)
{
	for (int y = 0; y < 4; y++)
		if (playfieldArr[tetrominoY + y][0] == 'o' && playfieldArr[tetrominoY + y][1] == 'o' && playfieldArr[tetrominoY + y][2] == 'o'  && playfieldArr[tetrominoY + y][3] == 'o'  && playfieldArr[tetrominoY + y][4] == 'o'  && playfieldArr[tetrominoY + y][5] == 'o' && playfieldArr[tetrominoY + y][6] == 'o' && playfieldArr[tetrominoY + y][7] == 'o' && playfieldArr[tetrominoY + y][8] == 'o' && playfieldArr[tetrominoY + y][9] == 'o')
			for (int x = 0; x < PLAYFIELD_X; x++)
			{
				playfieldArr[tetrominoY + y][x] = ' ';	
				for (int i = tetrominoY + y; i > 0; i--)
					playfieldArr[i][x] = playfieldArr[i - 1][x];
			}
}			