#include <time.h>
#include "header.h" 

int main()
{
	initscr();
	noecho();
	raw();
	cbreak();
	keypad(stdscr,TRUE);
	curs_set(0);
	
	checkWindow();

	//start_color();
	//initColour();

	startGame();

	while (isPlay)
	{	
		
		logic();
		//fall();

		updatePlayfield();
	}
	
	//some random stuff so the window won't close right after you hit esc
	clear();
	printw("hello world!");

	refresh();
	getch();

	
	
	endwin();
	return 0;
}