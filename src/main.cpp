#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>

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
	bool isActive;

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
		if(isActive)
		{
			chipPinkSprite.setPosition(64 + y_direction, 50);
		}		
	}

	void ChipMove(int dir, int &row)
	{
		cout << "row: " << row << "\n";

		if (dir == -1)
		{
			if (!(row < 1))
			{
				row -= 1;
				y_direction -= 74;
			}
		}

		else if (dir == 1)
		{
			if (!(row > 6))
			{
				row += 1;
				y_direction += 74;
			}
		}
		else
		{
			cout << "OUT OF BOUNDS" << "\n";
		}
	}

	void ChipSubmit(int rowHeights[5], int &row)
	{
		for (int i = 0; i <= rowHeights[row]; i++)
		{
			x_direction += 74;
		}

		rowHeights[row] -= 1;

		SetChipInBoard();		
	}

private:
	sf::Texture chipPinkTexture;
	sf::Sprite chipPinkSprite;

	int y_direction = 0;
	int x_direction = 0;

	void SetChipOrigin()
	{
		sf::Vector2u size = chipPinkTexture.getSize();
		chipPinkSprite.setOrigin(size.x / 2, size.y / 2);
		chipPinkSprite.setPosition(64 + y_direction, 50 + x_direction);
	}

	void SetChipInBoard()
	{
		chipPinkSprite.setPosition(64 + y_direction, 50 + x_direction);
		isActive = false;
	}
};

void main(int argc, char** argv[])
{  
	// The render window
	sf::RenderWindow window(sf::VideoMode(640, 480), "First Window");

	Clock _timer;

	board _board;

	//the chips
	vector<chip*> _chips;
	_chips.push_back(new chip);

	chip *_activeChip = _chips.back();

	int rowHeights[5] = { 4, 4, 4, 4, 4 };
	int row = 0;

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
					_activeChip->ChipSubmit(rowHeights, row);
					_chips.push_back(new chip);
					_activeChip = _chips.back();
				}

				if (event.key.code == sf::Keyboard::Left)
				{
					_activeChip->ChipMove(-1, row);
				}

				if (event.key.code == sf::Keyboard::Right)
				{
					_activeChip->ChipMove(1, row);
				}

			}
		}

		_activeChip->update();

		window.clear(sf::Color(236,240,241,255));

		//draw table		
		_board.DrawBoard(window);

		//draw chip
		for (int i = 0; i < _chips.size(); i++)
		{
			_chips[i]->draw(window);
		}

		//Draw here
		window.display();
	}
}
