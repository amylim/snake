#pragma once
#include "Tile.h"
#include <vector>
#include <queue>
#include <iostream>

enum Direction {LEFT, RIGHT, UP, DOWN};

class Snake
{
public:
	Snake(int x = 10, int y = 10);
	~Snake(void);
	void move();
	void changeDirection(int newDirection);
	void makeBodyLonger(int addLength);
	bool isBodyPart(int x, int y);
	bool hasHitItself();

	int setBodyLength(int length);

	std::queue<Tile> getBody();
	Tile getHead();
	int getBodyLength();
	int getDisplayedBodyLength();

private:
	int direction;
	int bodyLength;
	int displayedBodyLength;
	std::queue<Tile> body;
};

