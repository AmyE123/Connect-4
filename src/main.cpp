#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include <event.xsd>
using namespace std;
using namespace sf;

class Entity
{
public:
	virtual void update() {};

	virtual void draw(sf::RenderWindow& window, sf::Sprite sprite)
	{
		window.draw(sprite);
	}

	virtual ~Entity() {};
};

class board : public Entity
{
public:
	board()
	{
		boardTexture.loadFromFile("assets/boardGap.png");
		boardSprite.setTexture(boardTexture);		
	}
	
	void DrawBoard(sf::RenderWindow& window)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				sf::Texture boardTexture2;

				sf::Vector2u size3 = boardTexture.getSize();
				boardSprite.setOrigin(size3.x / 2, size3.y / 2);

				//50, 50 is top left corner
				boardSprite.setPosition(64 + (i * 74), 124 + (j * 74));
				draw(window);
			}
		}
	}

	void draw(sf::RenderWindow& window)
	{
		Entity::draw(window, boardSprite);
	}

private:
	sf::Texture boardTexture;
	sf::Sprite boardSprite;


};

class chip : public Entity
{
public:
	chip()
	{
		chipPinkTexture.loadFromFile("assets/chipPink.png");
		chipPinkSprite.setTexture(chipPinkTexture);
		
		SetChipOrigin();
	}

	void draw(sf::RenderWindow& window)
	{
		Entity::draw(window, chipPinkSprite);
	}

	void update()
	{
		Clock timer;
				
		//if (event.type == sf::Keyboard::Left)
		//{
		//	if (!(row < 1))
		//	{
		//		row -= 1;
		//		y_direction -= 74;
		//	}
		//}

		//if (event.type == sf::Keyboard::Right)
		//{
		//	if (!(row > 6))
		//	{
		//		row += 1;
		//		y_direction += 74;
		//	}
		//}

		//if (event.type == sf::Keyboard::Space)
		//{
		//	//ChipSubmit();
		//}
			

		// Delay for input
		//if (timer.getElapsedTime().asMilliseconds() >= 100)
		//{
		//	if (Keyboard::isKeyPressed(Keyboard::Left))
		//	{
		//		if (!(row < 1))
		//		{
		//			row -= 1;
		//			y_direction -= 74;
		//		}
		//	}

		//	if (Keyboard::isKeyPressed(Keyboard::Right))
		//	{
		//		if (!(row > 6))
		//		{
		//			row += 1;
		//			y_direction += 74;
		//		}
		//	}

		//	if (Keyboard::isKeyPressed(Keyboard::Space))
		//	{
		//		for (int i = 0; i <= rowHeights[row]; i++)
		//		{
		//			x_direction += 74;
		//		}

		//		rowHeights[row] -= 1;
		//	}

		//	timer.restart();
		//}

		chipPinkSprite.setPosition(64 + y_direction, 50 + x_direction);
	}

	void ChipMove()
	{
		
	}

	void ChipSubmit()
	{
		for (int i = 0; i <= rowHeights[row]; i++)
		{
			x_direction += 74;
		}

		rowHeights[row] -= 1;
	}

private:
	sf::Texture chipPinkTexture;
	sf::Sprite chipPinkSprite;

	int y_direction = 0;
	int x_direction = 0;

	int rowHeights[5] = { 4, 4, 4, 4, 4 };
	int row = 0;

	void SetChipOrigin()
	{
		sf::Vector2u size = chipPinkTexture.getSize();
		chipPinkSprite.setOrigin(size.x / 2, size.y / 2);
	}
};

void main(int argc, char** argv[])
{  
	// The render window
	sf::RenderWindow window(sf::VideoMode(640, 480), "First Window");

	Clock _timer;

	board _board;

	//the main chip
	chip _chip;	

	// Main gameplay loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed())
			{
				//Closed window button clicked
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					//_chip.DoSpaceBarStuff();
					_chip.ChipSubmit();
				}
			}
		}

		//updates every frame or so, so always sets back to origin? something to do with the loop or somethin
		// something is setting it back to 0
		_chip.update();

		window.clear(sf::Color(236,240,241,255));

		//draw table		
		_board.DrawBoard(window);

		//draw chip
		_chip.draw(window);

		//Draw here
		window.display();
	}
}
