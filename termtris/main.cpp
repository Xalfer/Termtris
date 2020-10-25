#include <time.h>
#include "main.h" 

int main()
{
	initscr();
	noecho();
	raw();
	cbreak();
	keypad(stdscr,true);
	curs_set(0);
	

	//start_color();
	
	checkWindow();

	startGame();
	
	//some random stuff so the window won't close right after you hit esc
	clear();
	printw("hello world!");

	refresh();
	getch();

	
	
	endwin();
	return 0;
}