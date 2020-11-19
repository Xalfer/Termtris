#pragma once

#define playfieldY 20
#define playfieldX 10

extern char playfieldArr[playfieldY][playfieldX];

struct win
{
	int height, width, posY, posX;

	WINDOW* win;

	void update() //this function is used for updating the playfield
	{

		const int blockSize = height / playfieldY;

		for (short y = 0; y < playfieldY * blockSize; y++)
		{
			for (short x = 0; x < playfieldX * blockSize; x++)
			{
				//attron(COLOR_PAIR(2));

				mvwprintw(win, y, x, "%c", playfieldArr[y / blockSize][x / blockSize]);

				//attroff(COLOR_PAIR(2));
			}
		}
		wrefresh(win);
		refresh();
	}
};