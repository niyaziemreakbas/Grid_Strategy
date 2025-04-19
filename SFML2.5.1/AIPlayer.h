#pragma once

#include "Player.h"
#include "Grid.h"

class AIPlayer : public Player {
public:
    AIPlayer(bool aiControlled, sf::Color soldierColor);

    // D��man asker �retme fonksiyonu
    void produceSoldier(Grid& grid);

};

