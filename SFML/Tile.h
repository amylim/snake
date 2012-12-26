#pragma once

// a square section of the screen
struct Tile
{
	Tile(int xpos = 0, int ypos = 0, int len = 10);
	~Tile(void);

	int x;
	int y;
	int length;
};

