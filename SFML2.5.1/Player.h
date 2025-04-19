#pragma once
#include <vector>
#include "Soldier.h"

class Player {
public:
    Player(bool isAI, sf::Color soldierColor);

    void addGold(int amount);
    bool spendGold(int amount);
    int getGold() const;

    void addSoldier(Soldier soldier);
    std::vector<Soldier>& getSoldiers();
    bool isAIControlled() const;

    void startTurn();
    void endTurn();


    sf::Color getSoldierColor() const;

private:
    bool aiControlled;
    int gold = 100;
    sf::Color soldierColor;
    std::vector<Soldier> soldiers;
};
