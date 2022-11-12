#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include "Entity.cpp"

using namespace std;
using namespace sf;

class Board : public Entity
{
public:
	Board()
	{
		if (!boardTexture.loadFromFile("assets/boardGap.png"))
		{
			cout << "Error loading board sprite" << "\n";
			return;
		}

		boardSprite.setTexture(boardTexture);	
	}
	
	void DrawBoard(sf::RenderWindow& window)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				sf::Vector2u size = boardTexture.getSize();
				boardSprite.setOrigin(size.x / 2, size.y / 2);

				//50, 50 is top left corner
				boardSprite.setPosition(64 + (i * 74), 124 + (j * 74));
				Draw(window);
			}
		}
	}

	void Draw(sf::RenderWindow& window)
	{
		Entity::Draw(window, boardSprite);
	}

private:
	sf::Texture boardTexture;
	sf::Sprite boardSprite;
};

class Chip : public Entity
{
public:
	bool isActive;

	Chip()
	{
		chipPinkTexture.loadFromFile("assets/chipPink.png");
		chipGreenTexture.loadFromFile("assets/chipGreen.png");

		chipPinkSprite.setTexture(chipPinkTexture);
		chipGreenSprite.setTexture(chipGreenTexture);
		
		SetChipOrigin();
	}

	void Draw(sf::RenderWindow& window, int idx)
	{
		Entity::Draw(window, idx % 2 == 0 ? chipPinkSprite : chipGreenSprite);
		chipIdx = idx;
	}

	void Update()
	{
		if(isActive)
		{
			sf::Sprite& spriteToMove = chipIdx % 2 == 0 ? chipPinkSprite : chipGreenSprite;
			spriteToMove.setPosition(64 + yDir, 50);			
		}		
	}

	void ChipMove(int dir, int& row)
	{
		if (dir == -1)
		{			
			if (!(row < 1))
			{
				row -= 1;
				yDir -= 74;
			}
			cout << "row: " << row << "\n";
		}

		else if (dir == 1)
		{
			
			if (!(row > 6))
			{
				row += 1;
				yDir += 74;
			}
			cout << "row: " << row << "\n";
		}
		else
		{
			cout << "OUT OF BOUNDS" << "\n";
		}
	}

	int ChipSubmit(int &rowHeight)
	{
		for (int i = 0; i <= rowHeight; i++)
		{
			x_direction += 74;
		}

		rowHeight -= 1;
		cout << "rowHeight: " << rowHeight << "\n";
		SetChipInBoard();
		return rowHeight;
	}

private:
	sf::Texture chipPinkTexture;
	sf::Sprite chipPinkSprite;

	sf::Texture chipGreenTexture;
	sf::Sprite chipGreenSprite;

	int yDir = 0;
	int x_direction = 0;

	int chipIdx;

	void SetChipOrigin()
	{
		const sf::Vector2u size = chipPinkTexture.getSize();
		chipPinkSprite.setOrigin(size.x / 2, size.y / 2);
		chipPinkSprite.setPosition(64 + yDir, 50 + x_direction);

		chipGreenSprite.setOrigin(size.x / 2, size.y / 2);
		chipGreenSprite.setPosition(64 + yDir, 50 + x_direction);
	}

	void SetChipInBoard()
	{
		chipPinkSprite.setPosition(64 + yDir, 50 + x_direction);
		chipGreenSprite.setPosition(64 + yDir, 50 + x_direction);

		isActive = false;
	}
};

void main(int argc, char** argv[])
{  
	// The render window
	sf::RenderWindow window(sf::VideoMode(640, 480), "First Window");

	Clock _timer;

	Board _board;

	//the chips
	vector<Chip*> _chips;
	_chips.push_back(new Chip);

	Chip *_activeChip = _chips.back();

	int rowHeights[8] = { 4, 4, 4, 4, 4, 4, 4, 4 };
	int row = 0;

	sf::Font font;

	if (!font.loadFromFile("assets/LouisGeorgeCafe.ttf"))
	{
		cout << "FONT ERROR" << "\n";
	}

	sf::Text text;

	text.setFont(font);
	text.setString("Connect 4");
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Green);

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
					if (rowHeights[row] != -1)
					{
						rowHeights[row] = _activeChip->ChipSubmit(rowHeights[row]);
						_chips.push_back(new Chip);
						_activeChip = _chips.back();
						row = 0;
					}
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

		_activeChip->Update();

		window.clear(sf::Color(236,240,241,255));

		//draw table		
		_board.DrawBoard(window);

		window.draw(text);

		//draw chip
		for (int i = 0; i < _chips.size(); i++)
		{
			_chips[i]->Draw(window, i);
		}	

		//Draw here
		window.display();
	}
}
