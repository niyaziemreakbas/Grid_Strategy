#pragma once
#include <SFML/Graphics.hpp>
#include "GridObject.h"

class Soldier : public GridObject {
public:
    Soldier(int x, int y, sf::Color color);
   
    void update(float dt) override;
	void draw(sf::RenderWindow& window) override;
    
    void toggleSelection(bool select);
    bool isSelected() const;
    bool contains(sf::Vector2f point) const;

    void setTargetPosition(int x, int y);
	sf::Vector2i getGridPosition() const override;
    bool isMovingNow() const { return isMoving; }

    bool hasMoved() const;
    void setMoved(bool moved);
	
    void resetMovePoints();
    void move(sf::Vector2i target);
    bool canMoveTo(sf::Vector2i target);
	int manhattanDistance(int x1,int x2,int y1,int y2);



private:
    sf::CircleShape shape;
    sf::Vector2f targetPosition;
    float speed = 100.f;

    bool selected = false;
	bool isMoving = false;
    bool moved = false;

    int maxMovePoints = 2;    // Toplam hareket hakký
    int currentMovePoints = 2; // Þu an kalan hareket hakký
    std::vector<sf::Vector2i> moveHistory; // Geçmiþ hareketler
};
