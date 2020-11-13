#include <curses.h>
#include "shapes.cpp"

#define playfieldY 20
#define playfieldX 10

struct wins
{
	int height, width, pos_y, pos_x;

	WINDOW* win;
};

char playfieldArr[playfieldY][playfieldX] = {};

wins playfield;


void drawPlayfield() //this function is used for resizing and drawing the windows
{
	border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

	wins border;


	//this handles resizing the border for the playfield
	border.height = LINES;
	
	while (border.height % playfieldY != 2)
	{
		border.height--;
	}

	border.width = (border.height / 2) + 1;


	border.pos_y = (LINES - border.height) / 2;
	border.pos_x = (COLS - border.width) / 2;


	border.win = newwin(border.height, border.width, border.pos_y, border.pos_x);

	wborder(border.win, ACS_VLINE, ACS_VLINE, ' ', ACS_HLINE, ACS_VLINE, ACS_VLINE, ACS_LLCORNER, ACS_LRCORNER);


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

	const int blockSize  = playfield.height / playfieldY;
	
	for (short y = 0; y < playfieldY * blockSize; y++) 
	{
		for (short x = 0; x < playfieldX * blockSize; x++)
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

			