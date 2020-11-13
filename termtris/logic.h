#pragma once
#include <curses.h>

#define playfieldY 20
#define playfieldX 10


void drawPlayfield();
void updatePlayfield();
void clearPlayfield();

extern char playfieldArr[playfieldY][playfieldX];
