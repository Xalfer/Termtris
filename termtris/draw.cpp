#include "header.h"
#include "shapes.cpp"

class wins
{
public:
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

void initColour() 
{
	init_color(8, 100, 0, 0);

	init_pair(1, 3, 2);
	init_pair(2, COLOR_BLUE, COLOR_GREEN);
	init_pair(3, COLOR_WHITE, COLOR_WHITE);
	init_pair(4, COLOR_BLACK, COLOR_YELLOW);
	init_pair(5, COLOR_BLACK, COLOR_GREEN);
	init_pair(6, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(7, COLOR_BLACK, COLOR_RED);
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
