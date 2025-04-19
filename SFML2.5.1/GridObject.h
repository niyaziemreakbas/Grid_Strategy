#pragma once
#include <SFML/Graphics.hpp>

class GridObject
{

public:
	virtual ~GridObject() = default;
	virtual void update(float dt) = 0;
	virtual sf::Vector2i getGridPosition() const = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
};

