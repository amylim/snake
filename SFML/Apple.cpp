#include "Apple.h"


Apple::Apple(int xmax, int ymax)
{
	/* initialize random seed: */
	srand ( time(NULL) );
	
	coord.x = round2ten(rand() % xmax);
	coord.y = round2ten(rand() % ymax);	
}

Apple::~Apple(void)
{
}

int Apple::getX()
{
	return coord.x;
}

int Apple::getY()
{
	return coord.y;
}

void Apple::regenerate(int xmax, int ymax)
{
	coord.x = round2ten(rand() % xmax);
	coord.y = round2ten(rand() % ymax);
}

int Apple::round2ten(int num)
{
	int remainder = num % 10;
	return num - remainder;
}