// AIPlayer.cpp
#include "AIPlayer.h"
#include "Grid.h"
#include <cstdlib>  // rand() fonksiyonu için

AIPlayer::AIPlayer(bool aiControlled, sf::Color soldierColor)
    : Player(aiControlled, soldierColor) {
}

void AIPlayer::produceSoldier(Grid& grid) {
    // Eðer yeterli altýn varsa, yeni asker üret
    if (this->getGold() >= 50) {
        // Random boþ bir kare bul
        for (int i = 0; i < 50; ++i) {
            int x = rand() % 10;
            int y = rand() % 10;

            bool occupied = false;
            for (const auto& s : this->getSoldiers()) {
                if (s.getGridPosition() == sf::Vector2i(x, y)) {
                    occupied = true;
                    break;
                }
            }

            if (!occupied) {
                this->addSoldier(Soldier(x, y, this->getSoldierColor()));
                this->spendGold(50);  // Asker üretildiðinde altýn harcandý
                break;
            }
        }
    }
}
