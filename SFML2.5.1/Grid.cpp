#include "Grid.h"

Grid::Grid(int sizeX, int sizeY, int cellSize, int gap)
    : gridSizeX(sizeX), gridSizeY(sizeY), cellSize(cellSize), gap(gap) {

    gridCells.resize(gridSizeX, std::vector<GridCell>(gridSizeY, GridCell(0, 0, cellSize, gap)));

    for (int i = 0; i < gridSizeX; ++i) {
        for (int j = 0; j < gridSizeY; ++j) {
            gridCells[i][j] = GridCell(i, j, cellSize, gap);
        }
    }
}

void Grid::draw(sf::RenderWindow& window) {
    for (int i = 0; i < gridSizeX; ++i) {
        for (int j = 0; j < gridSizeY; ++j) {
            gridCells[i][j].draw(window);
        }
    }
}

GridCell* Grid::getCellAt(sf::Vector2f mousePos) {
    int x = static_cast<int>(mousePos.x) / (cellSize + gap);
    int y = static_cast<int>(mousePos.y) / (cellSize + gap);

    if (x < 0 || y < 0 || x >= gridSizeX || y >= gridSizeY)
        return nullptr;

    return &gridCells[x][y];
}

sf::Vector2i Grid::getGridPosition(sf::Vector2f mousePos) {
    int x = static_cast<int>(mousePos.x) / (cellSize + gap);
    int y = static_cast<int>(mousePos.y) / (cellSize + gap);

    if (x >= gridSizeX) x = gridSizeX - 1;
    if (y >= gridSizeY) y = gridSizeY - 1;

    return sf::Vector2i(x, y);
}

sf::Vector2i Grid::getGridSize() const {
    return sf::Vector2i(gridSizeX, gridSizeY);
}

const std::vector<std::vector<GridCell>>& Grid::getCells() const {
    return gridCells;
}
/*
const std::vector<std::vector<GridCell>>& Grid::getEmptyCells(Grid grid) const {
    for (const auto& s : grid.getCells()) {
        for (const auto& cell : s) {
            if (!cell.hasObject()) {
            }
        }
    }
                                

	return gridCells;
}
*/
