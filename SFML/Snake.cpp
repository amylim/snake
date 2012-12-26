#include "Snake.h"

Snake::Snake(int x, int y)
{
	//velocity = 1;
	direction = UP;
	bodyLength = 3;
	displayedBodyLength = 1;

	Tile head(x, y);
	body.push(head);
}

Snake::~Snake(void)
{
}

void Snake::move()
{
	Tile newHead = body.back();
	switch(direction)
	{
	case LEFT:
		newHead.x -= 10;
		break;
	case RIGHT:
		newHead.x += 10;
		break;
	case UP:
		newHead.y -= 10;
		break;
	case DOWN:
		newHead.y += 10;
		break;
	}
	body.push(newHead);
	displayedBodyLength++;

	//pop off any extra body parts
	if(displayedBodyLength > bodyLength)
	{
		body.pop();
		displayedBodyLength--;
	}
}

void Snake::changeDirection(int newDirection)
{
	//only allow change of direction if the new direction is not into the snake's body
	switch(newDirection)
	{
	case LEFT:
		if(direction != RIGHT)
		{
			std::cout << "left" << std::endl;
			direction = newDirection;
		}
		break;
	case RIGHT:
		if(direction != LEFT)
		{
			std::cout << "right" << std::endl;
			direction = newDirection;
		}
		break;
	case UP:
		if(direction != DOWN)
		{
			std::cout << "up" << std::endl;
			direction = newDirection;
		}
		break;
	case DOWN:
		if(direction != UP)
		{
			std::cout << "down" << std::endl;
			direction = newDirection;
		}
		break;
	}
}

void Snake::makeBodyLonger(int addLength)
{
	bodyLength += addLength;
}


bool Snake::isBodyPart(int x, int y)
{
	std::queue<Tile> tempBody = getBody();
	int length = getDisplayedBodyLength();

	//check if the coordinates match any of the body parts
	//NOTE: length has to be >1 because the last body part is the head;
	//		only checks the upper left corner of the body parts
	while(!(tempBody.front().x == x && tempBody.front().y == y) && length > 1)
	{
		tempBody.pop();
		length--;
	}

	if(length == 1)
		return false;
	return true;
}
bool Snake::hasHitItself()
{
	return isBodyPart(getHead().x, getHead().y);
}

std::queue<Tile> Snake::getBody()
{
	return body;
}

Tile Snake::getHead()
{
	return getBody().back();
}

int Snake::getBodyLength()
{
	return bodyLength;
}

int Snake::getDisplayedBodyLength()
{
	return displayedBodyLength;
}
