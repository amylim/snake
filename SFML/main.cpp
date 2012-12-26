#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include <Windows.h>
#include "Snake.h"
#include "Apple.h"

const static int FRAME_WIDTH = 400;
const static int FRAME_HEIGHT = 300;
const static int START_SPEED = 10;

sf::Sprite** createSnakeSprite(Snake s);
sf::Sprite* createAppleSprite(Apple a);
bool isAppleEaten(Snake s, Apple a);
bool hasHitWall(Snake s);
void levelUp(Snake &s, Apple &a, int &speed);
void startGame(Snake &s, Apple &a, int &speed);

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(FRAME_WIDTH, FRAME_HEIGHT), "Snake");

	//---------------snake stuff--------------------
	Snake snake(FRAME_WIDTH / 2, FRAME_HEIGHT / 2);
	Apple apple(FRAME_WIDTH, FRAME_HEIGHT);
	int speed = START_SPEED;

	bool isStarted = false;
	bool isGameOver = false;
	bool isPaused = false;

	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window : exit
			if (event.type == sf::Event::Closed)
				window.close();

			if(event.type == sf::Event::KeyPressed)
			{
				switch(event.key.code)
				{
				case sf::Keyboard::Left:
					snake.changeDirection(LEFT);
					//snake.move();
					break;
				case sf::Keyboard::Right:
					snake.changeDirection(RIGHT);
					//snake.move();
					break;
				case sf::Keyboard::Up:
					snake.changeDirection(UP);
					//snake.move();
					break;
				case sf::Keyboard::Down:
					snake.changeDirection(DOWN);
					//snake.move();
					break;
				case sf::Keyboard::Space:
					isGameOver = false;
					startGame(snake, apple, speed);
					break;
				case sf::Keyboard::P:
					isPaused = !isPaused;
					std::cout << "Paused game" << std::endl;
					break;
				}
			}
		}

		if(!isStarted)
		{
			window.clear();

			//Display the start screen
			sf::Font font;
			if (!font.loadFromFile("arial.ttf"))
				return EXIT_FAILURE;
			sf::Text text1("Snake", font, 50);
			text1.setPosition(FRAME_WIDTH/2 - text1.getGlobalBounds().width/2, FRAME_HEIGHT/3);
			window.draw(text1);

			sf::Text text2("Press 'spacebar' to start", font, 30);
			text2.setPosition(FRAME_WIDTH/2 - text2.getGlobalBounds().width/2, FRAME_HEIGHT/3 + text1.getGlobalBounds().height);
			window.draw(text2);

			window.display();

			while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				Sleep(100);
			}

			isStarted = true;
		}
		else
		{
			if(isPaused)
			{
				//Display the pause screen
				sf::Font font;
				if (!font.loadFromFile("arial.ttf"))
					return EXIT_FAILURE;
				sf::Text text("Paused", font, 30);
				text.setPosition(FRAME_WIDTH/2 - text.getGlobalBounds().width/2, FRAME_HEIGHT/2);
				window.draw(text);

				window.display();

				while(!sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				{
					Sleep(100);
				}
			}
			else
			{
				// Clear screen
				window.clear();

				// Draw the snake
				sf::Sprite **snakeSprite = createSnakeSprite(snake);
				for(int i = 0; i < snake.getDisplayedBodyLength(); i++)
				{
					window.draw(*snakeSprite[i]);
				}

				// Draw the apple
				sf::Sprite *appleSprite = createAppleSprite(apple);
				window.draw(*appleSprite);

				//display window
				window.display();

				if(!isGameOver) 
				{
					snake.move();

					//check if the snake has hit a wall
					if(hasHitWall(snake))
					{
						std::cout << "wall hit" << std::endl;
						isGameOver = true;
					}

					//check if the snake has hit its body
					if(snake.hasHitItself())
					{
						std::cout << "self collision" << std::endl;
						isGameOver = true;
					}

					//check if the snake ate an apple
					if(isAppleEaten(snake, apple))
					{
						std::cout << "apple has been eatten" << std::endl;
						levelUp(snake, apple, speed);
					}

					Sleep(1000/speed);
				}
				else
				{
					//Display the game over screen
					sf::Font font;
					if (!font.loadFromFile("arial.ttf"))
						return EXIT_FAILURE;
					sf::Text text1("Game Over", font, 30);
					text1.setPosition(FRAME_WIDTH/2 - text1.getGlobalBounds().width/2, FRAME_HEIGHT/2);
					window.draw(text1);

					sf::Text text2("Press 'spacebar' to restart", font, 30);
					text2.setPosition(FRAME_WIDTH/2 - text2.getGlobalBounds().width/2, FRAME_HEIGHT/2 + text1.getGlobalBounds().height);
					window.draw(text2);

					window.display();

					while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					{
						Sleep(100);
					}
				}

			}
		}
	}

	return 0;
}

sf::Sprite** createSnakeSprite(Snake s)
{
	std::queue<Tile> snakeParts = s.getBody();
	sf::Texture *snakeTexture = new sf::Texture();
	snakeTexture->loadFromFile("snake.png");

	int bodyLength = s.getDisplayedBodyLength();
	sf::Sprite **snakeSprite = new sf::Sprite*[bodyLength];
	for (int i = 0; i < bodyLength; i++)
	{
		snakeSprite[i] = new sf::Sprite(*snakeTexture);
		Tile snakePart = snakeParts.front();
		snakeParts.pop();
		snakeSprite[i]->setPosition(snakePart.x, snakePart.y);
	}

	return snakeSprite;
}

sf::Sprite* createAppleSprite(Apple a)
{
	sf::Texture *appleTexture = new sf::Texture();
	appleTexture->loadFromFile("apple.png");

	sf::Sprite *appleSprite = new sf::Sprite(*appleTexture);
	appleSprite->setPosition(a.getX(), a.getY());

	return appleSprite;
}

bool isAppleEaten(Snake s, Apple a)
{
	return (s.getHead().x == a.getX() && s.getHead().y == a.getY());
}

bool hasHitWall(Snake s)
{
	return (s.getHead().x < 0 || s.getHead().x >= FRAME_WIDTH || s.getHead().y < 0 || s.getHead().y >= FRAME_HEIGHT);
}

void levelUp(Snake &s, Apple &a, int &speed)
{
	do
	{
		a.regenerate(FRAME_WIDTH, FRAME_HEIGHT);
	} while(s.isBodyPart(a.getX(), a.getY()));
	s.makeBodyLonger(1);
	speed++;
}

void startGame(Snake &s, Apple &a, int &speed)
{
	s = Snake(FRAME_WIDTH / 2, FRAME_HEIGHT / 2);
	do
	{
		a.regenerate(FRAME_WIDTH, FRAME_HEIGHT);
	} while(s.isBodyPart(a.getX(), a.getY()));
	speed = START_SPEED;
}