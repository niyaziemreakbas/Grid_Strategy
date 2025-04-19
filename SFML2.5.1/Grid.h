#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "GridCell.h"

class Grid {
public:
    Grid(int sizeX, int sizeY, int cellSize, int gap);

    void draw(sf::RenderWindow& window);
    sf::Vector2i getGridPosition(sf::Vector2f mousePos);
    sf::Vector2i getGridSize() const;

    const std::vector<std::vector<GridCell>>& getCells() const;

    GridCell* getCellAt(sf::Vector2f mousePos);

    const std::vector<std::vector<GridCell>>& getEmptyCells() const;

private:
    int gridSizeX;
    int gridSizeY;
    int cellSize;
    int gap;
    std::vector<std::vector<GridCell>> gridCells;
};

#endif
