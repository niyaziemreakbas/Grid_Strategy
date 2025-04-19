#include "GridCell.h"

GridCell::GridCell(int gridX, int gridY, float size, float gap)
    : gridX(gridX), gridY(gridY), isHighlighted(false) {
    shape.setSize(sf::Vector2f(size - gap, size - gap));
    shape.setPosition(gridX * (size + gap), gridY * (size + gap));
    shape.setFillColor(sf::Color::Green);
}

void GridCell::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::Vector2i GridCell::getGridPosition() const {
    return sf::Vector2i(gridX, gridY);
}

sf::Vector2f GridCell::getPixelPosition() const {
    return shape.getPosition();
}

bool GridCell::contains(const sf::Vector2f& point) const {
    return shape.getGlobalBounds().contains(point);
}

void GridCell::setHighlight(bool highlight) {
    isHighlighted = highlight;
    if (highlight)
        shape.setFillColor(sf::Color(255, 165, 0));
    else
        shape.setFillColor(sf::Color::Green);
}

void GridCell::setColor(const sf::Color& color) {
    shape.setFillColor(color);
}

void GridCell::setObject(GridObject* obj) {
    objectOnCell = obj;
}

GridObject* GridCell::getObject() const {
    return objectOnCell;
}

bool GridCell::hasObject() const {
    return objectOnCell != nullptr;
}

void GridCell::clearObject() {
    objectOnCell = nullptr;
}