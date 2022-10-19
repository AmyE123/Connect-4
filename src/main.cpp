#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
using namespace std;
using namespace sf;

sf::Sprite createChip(sf::Texture chipPinkTexture)
{
	sf::Sprite chipPinkSprite(chipPinkTexture);
	sf::Vector2u size = chipPinkTexture.getSize();
	chipPinkSprite.setOrigin(size.x / 2, size.y / 2);

	return chipPinkSprite;
}

void main(int argc, char** argv[])
{  
	sf::RenderWindow window(sf::VideoMode(640, 480), "First Window");
	
	sf::Texture chipGreenTexture;

	Clock timer;

	sf::Texture chipPinkTexture;
	chipPinkTexture.loadFromFile("assets/chipPink.png");
	
	sf::Sprite chipPinkSprite(chipPinkTexture);

	vector<sf::Sprite> activeSprite;
	

	sf::Vector2u size = chipPinkTexture.getSize();
	chipPinkSprite.setOrigin(size.x / 2, size.y / 2);

	int y_direction = 0;
	int x_direction = 0;

	int row = 0;
	int rowHeights[5] = {4, 4, 4, 4, 4};
	int chipIndex = 0;

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
		}
		//sf::Sprite a = new sf::Sprite(chipPinkTexture);
		activeSprite.push_back(chipPinkSprite);

		// Delay for input
		if (timer.getElapsedTime().asMilliseconds() >= 100)
		{
			if (Keyboard::isKeyPressed(Keyboard::Left)) 
			{ 
				if (!(row < 1)) 
				{ 
					row -= 1; 
					y_direction -= 74;
				}
				
				
			}

			if (Keyboard::isKeyPressed(Keyboard::Right)) 
			{ 
				if (!(row > 6)) 
				{ 
					row += 1; 
					y_direction += 74;
				}				
			}

			if (Keyboard::isKeyPressed(Keyboard::Space)) 
			{
				activeSprite.push_back(chipPinkSprite);
				chipIndex += 1;

				for (int i = 0; i <= rowHeights[row]; i++)
				{				
					x_direction += 74;
				}

				rowHeights[row] -= 1;				
			}

			timer.restart();
		}

		//chip[chipIndex].setPosition(64 + y_direction, 50 + x_direction);
		chipPinkSprite.setPosition(64 + y_direction, 50 + x_direction);
		//activeSprite.end()->setPosition(64 + y_direction, 50 + x_direction);
		//activeSprite.setPosition(64 + y_direction, 50 + x_direction);

		window.clear(sf::Color(236,240,241,255));

		//draw table
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				sf::Texture boardTexture2;

				boardTexture2.loadFromFile("assets/boardGap.png");
				sf::Sprite boardSprite2(boardTexture2);
				sf::Vector2u size3 = boardTexture2.getSize();
				boardSprite2.setOrigin(size3.x / 2, size3.y / 2);

				//50, 50 is top left corner
				boardSprite2.setPosition(64 + (i * 74), 124 + (j * 74));
				window.draw(boardSprite2);
			}
		}

		//Draw here
		window.draw(chipPinkSprite);
		

		window.display();
	}
}
