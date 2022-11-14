#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include "Entity.h"

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
	enum direction { Left, Right };
	enum player { Player1, Player2 };
	bool isActive;

	Chip()
	{
		if (!chipPinkTexture.loadFromFile("assets/chipPink.png") || !chipGreenTexture.loadFromFile("assets/chipGreen.png"))
		{
			cout << "TEXTURE ERROR" << "\n";
		}

		chipPinkSprite.setTexture(chipPinkTexture);
		chipGreenSprite.setTexture(chipGreenTexture);
		
		SetChipOrigin();
	}

	void Draw(sf::RenderWindow& window, player Player)
	{
		Entity::Draw(window, Player == Player1 ? chipPinkSprite : chipGreenSprite);

		currentPlayer = Player;
	}

	void Update()
	{
		if(isActive)
		{
			sf::Sprite& spriteToMove = currentPlayer == Player1 ? chipPinkSprite : chipGreenSprite;
			spriteToMove.setPosition(64 + yDir, 50);			
		}		
	}

	void ChipMove(direction direction, int& row)
	{
		if (direction == Left)
		{
			if (!(row < 1))
			{
				row -= 1;
				yDir -= 74;
			}
		}

		if (direction == Right)
		{
			if (!(row > 6))
			{
				row += 1;
				yDir += 74;
			}
		}
	}

	int ChipSubmit(int rowHeight)
	{
		for (int i = 0; i <= rowHeight; i++)
		{
			xDir += 74;
		}

		rowHeight -= 1;
		SetChipInBoard();
		return rowHeight;
	}

private:
	sf::Texture chipPinkTexture;
	sf::Sprite chipPinkSprite;

	sf::Texture chipGreenTexture;
	sf::Sprite chipGreenSprite;

	int yDir = 0;
	int xDir = 0;

	player currentPlayer;

	void SetChipOrigin()
	{
		const sf::Vector2u size = chipPinkTexture.getSize();
		chipPinkSprite.setOrigin(size.x / 2, size.y / 2);
		chipPinkSprite.setPosition(64 + yDir, 50 + xDir);

		chipGreenSprite.setOrigin(size.x / 2, size.y / 2);
		chipGreenSprite.setPosition(64 + yDir, 50 + xDir);
	}

	void SetChipInBoard()
	{
		chipPinkSprite.setPosition(64 + yDir, 50 + xDir);
		chipGreenSprite.setPosition(64 + yDir, 50 + xDir);

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
					_activeChip->ChipMove(Chip::direction::Left, row);
				}

				if (event.key.code == sf::Keyboard::Right)
				{
					_activeChip->ChipMove(Chip::direction::Right, row);
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
			Chip::player player = i % 2 == 0 ? Chip::Player1 : Chip::Player2;

			_chips[i]->Draw(window, player);
		}	

		//Draw here
		window.display();
	}
}
