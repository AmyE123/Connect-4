#include <SFML/Graphics.hpp>
using namespace sf;

class Entity
{
public:
	virtual void update() {};
	virtual void draw(RenderWindow& window, Sprite sprite);
	virtual ~Entity() {};
};