#include "Player.h"

Player::Player(bool isAI, sf::Color color)
    : aiControlled(isAI), soldierColor(color) {
}

void Player::addGold(int amount) {
    gold += amount;
}

bool Player::spendGold(int amount) {
    if (gold >= amount) {
        gold -= amount;
        return true;
    }
    return false;
}

int Player::getGold() const {
    return gold;
}

void Player::addSoldier(Soldier soldier) {
    soldiers.push_back(soldier);
}

std::vector<Soldier>& Player::getSoldiers() {
    return soldiers;
}

bool Player::isAIControlled() const {
    return aiControlled;
}

void Player::startTurn() {
	for (auto& s : soldiers) {
		s.setMoved(false); // Askerlerin hareket durumunu sýfýrla
	}
    addGold(20);
}

void Player::endTurn() {
}



sf::Color Player::getSoldierColor() const {
    return soldierColor;
}
