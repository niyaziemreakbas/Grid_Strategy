#pragma once

#include "Player.h"
#include "Grid.h"

class AIPlayer : public Player {
public:
    AIPlayer(bool aiControlled, sf::Color soldierColor);

    // Düþman asker üretme fonksiyonu
    void produceSoldier(Grid& grid);

};

