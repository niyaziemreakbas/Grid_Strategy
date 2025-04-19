#include "Soldier.h"

Soldier::Soldier(int x, int y, sf::Color color) {
    shape.setRadius(15);
    shape.setOrigin(18, 18); // merkeze almak i�in
    shape.setFillColor(color);
    shape.setPosition(x * 42 + 21, y * 42 + 21); // h�crenin merkezine koy
    targetPosition = shape.getPosition();
}

void Soldier::update(float dt) {
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f dir = targetPosition - pos;
    float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    if (dist > 1.0f) {
        sf::Vector2f norm = dir / dist;
        shape.move(norm * speed * dt);
    }
    else {
        shape.setPosition(targetPosition);
        isMoving = false;  // >>>> ARTIK HAREKET ETM�YOR <<<<
    }
}

void Soldier::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Soldier::toggleSelection(bool select) {
    selected = select;
    shape.setOutlineThickness(selected ? 3.f : 0.f);
    shape.setOutlineColor(sf::Color::Black);
}

bool Soldier::isSelected() const {
    return selected;
}

bool Soldier::hasMoved() const {
    return moved;
}

void Soldier::setMoved(bool m) {
    moved = m;
}

bool Soldier::contains(sf::Vector2f point) const {
    return shape.getGlobalBounds().contains(point);
}

void Soldier::resetMovePoints() {
    currentMovePoints = maxMovePoints;
    moveHistory.clear();
}

void Soldier::setTargetPosition(int gridX, int gridY) {
    sf::Vector2f newTarget(gridX * 42 + 21, gridY * 42 + 21);
    if (targetPosition != newTarget) {
        targetPosition = newTarget;
        isMoving = true;
		moved = true;  // Asker hareket etti
    }
}

sf::Vector2i Soldier::getGridPosition() const {
    sf::Vector2f pos = shape.getPosition();
    return sf::Vector2i(static_cast<int>(pos.x) / 42, static_cast<int>(pos.y) / 42);
}

//void Soldier::move(sf::Vector2i target) {
//    // Hedefe hareketin ge�erli olup olmad���n� kontrol et
//    if (canMoveTo(target)) {
//        // Hareketi ger�ekle�tir
//        shape.setPosition(target.x * 42 + 21, target.y * 42 + 21);
//
//        // Bu kareyi ge�irdi�imiz hareketler listesine ekle
//        moveHistory.push_back(target);
//
//        // Hareket puan�n� azalt
//        currentMovePoints -= 1;  // Her bir h�cre hareketi 1 puan azalt�r
//
//        // E�er hareket puan� s�f�rlan�rsa, art�k ba�ka bir hamle yap�lamaz
//        if (currentMovePoints <= 0) {
//            // Hareket k�s�tlamas�
//        }
//    }
//}


// Hareketin ge�erli olup olmad���n� kontrol et
bool Soldier::canMoveTo(sf::Vector2i target) {
    // Son hareketi takip et
    if (moveHistory.size() > 0 && target == moveHistory.back()) {
        return false;  // Geri hareket etmeyi engelle
    }

    // Manhattan mesafesi hesapla
    int dist = manhattanDistance(getGridPosition().x, getGridPosition().y, target.x, target.y);

    // E�er mesafe mevcut hareket puan�ndan k���kse ge�erli hareket
    return dist <= currentMovePoints;
}

// Hareketin do�ru bir �ekilde ger�ekle�tirildi�ini kontrol et
int Soldier::manhattanDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

