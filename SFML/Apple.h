#pragma once
#include "Tile.h"
#include <Windows.h>
#include <time.h>

class Apple
{
public:
	Apple(int xmax = 800, int ymax = 600);
	~Apple(void);

	int getX();
	int getY();
	void regenerate(int xmax, int ymax);

private:
	Tile coord;

	int round2ten(int num);
};

