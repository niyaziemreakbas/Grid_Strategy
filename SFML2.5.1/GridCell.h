#pragma once
#include <SFML/Graphics.hpp>
#include "GridObject.h"

class GridCell {
public:
    GridCell(int gridX, int gridY, float size, float gap);

    void draw(sf::RenderWindow& window) const;
    sf::Vector2i getGridPosition() const;
    sf::Vector2f getPixelPosition() const;
    bool contains(const sf::Vector2f& point) const;
    void setHighlight(bool highlight);
    void setColor(const sf::Color& color);

    void setObject(GridObject* obj);
    GridObject* getObject() const;
    void clearObject();
    bool hasObject() const;

private:
    int gridX, gridY;
    sf::RectangleShape shape;
    bool isHighlighted;
    GridObject* objectOnCell = nullptr;

};
