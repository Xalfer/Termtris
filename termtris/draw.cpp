#include <curses.h>

#include "shapes.cpp"
#include "win.h"





char playfieldArr[playfieldY][playfieldX] = {};


void drawPlayfield(win* winArr[2]) //this function is used for resizing and drawing the windows
{
	border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);


	//this handles resizing the border for the playfield
	win playfieldBorder;

	playfieldBorder.height = LINES;
	
	while (playfieldBorder.height % playfieldY != 2)
	{
		playfieldBorder.height--;
	}

	playfieldBorder.width = (playfieldBorder.height / 2) + 1;


	playfieldBorder.posY = (LINES - playfieldBorder.height) / 2;
	playfieldBorder.posX = (COLS - playfieldBorder.width) / 2;


	playfieldBorder.win = newwin(playfieldBorder.height, playfieldBorder.width, playfieldBorder.posY, playfieldBorder.posX);

	wborder(playfieldBorder.win, ACS_VLINE, ACS_VLINE, ' ', ACS_HLINE, ACS_VLINE, ACS_VLINE, ACS_LLCORNER, ACS_LRCORNER);


	//this makes the playfield window
	winArr[0]->height	= playfieldBorder.height - 2;
	winArr[0]->width	= playfieldBorder.width - 2;
	winArr[0]->posY		= playfieldBorder.posY + 1;
	winArr[0]->posX		= playfieldBorder.posX + 1;

	winArr[0]->win = newwin(winArr[0]->height, winArr[0]->width, winArr[0]->posY, winArr[0]->posX);


	//this makes the border for the preview window
	win previewBorder;

	previewBorder.height	= (4 * 4 * winArr[0]->height / playfieldY) + 2; //this work like (number of pieces * the size of the piece * the size of the individual blocks)
	previewBorder.width		= (1 * 4 * winArr[0]->width / playfieldX) + 2;
	previewBorder.posY		= playfieldBorder.posY;
	previewBorder.posX		= playfieldBorder.posX + playfieldBorder.width + 1;

	previewBorder.win = newwin(previewBorder.height, previewBorder.width, previewBorder.posY, previewBorder.posX);

	box(previewBorder.win, 0, 0);

	//this makes the preview window
	winArr[1]->height	= previewBorder.height - 2;
	winArr[1]->width	= previewBorder.width - 2;
	winArr[1]->posY		= previewBorder.posY + 1;
	winArr[1]->posX		= previewBorder.posX + 1;

	winArr[1]->win = newwin(winArr[1]->height, winArr[1]->width, winArr[1]->posY, winArr[1]->posX);

	refresh();
	wrefresh(playfieldBorder.win);
	wrefresh(previewBorder.win);
	wrefresh(winArr[0]->win);
	wrefresh(winArr[1]->win);
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

			