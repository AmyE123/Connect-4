#include <SFML/Graphics.hpp>

class Entity
{
public:
	virtual void update() {};
	virtual void Draw(sf::RenderWindow& window, sf::Sprite& sprite);
	virtual ~Entity() {};
};