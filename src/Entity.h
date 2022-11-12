#include <SFML/Graphics.hpp>
using namespace sf;

class Entity
{
public:
	virtual void update() {};
	virtual void Draw(RenderWindow& window, Sprite sprite);
	virtual ~Entity() {};
};