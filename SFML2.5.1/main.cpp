// main.cpp
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Grid.h"
#include "Utils.h"
#include "Player.h"
#include "AIPlayer.h"  // Yeni eklenen AIPlayer sınıfı

#include <vector>
#include <ctime>

const int gridSize = 10;
const int cellSize = 40;
const int gap = 2;

int main() {
    srand(static_cast<unsigned>(time(0)));

    sf::RenderWindow window(sf::VideoMode(1000, 800), "Turn-Based Strategy");
    sf::Clock clock;
    Grid grid(gridSize, gridSize, cellSize, gap);

    // UI
    Button endTurnBtn({ 850, 50 }, { 100, 40 }, "End Turn");
    Button newSoldierBtn({ 850, 100 }, { 100, 40 }, "New Soldier");
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    sf::Text goldText("", font, 16);
    goldText.setPosition(850, 10);
    goldText.setFillColor(sf::Color::Yellow);

    // Players
    Player player(false, sf::Color::Blue);
    AIPlayer enemy(true, sf::Color::Red);  // AIPlayer kullanıldı

    // İlk askerler
    player.addSoldier(Soldier(0, 0, player.getSoldierColor()));
    enemy.addSoldier(Soldier(8, 8, enemy.getSoldierColor()));

    Player* currentPlayer = &player;
    Player* otherPlayer = &enemy;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (!currentPlayer->isAIControlled()) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    sf::Vector2i clickedGrid = grid.getGridPosition(mousePos);

                    if (endTurnBtn.isClicked(mousePos)) {
                        currentPlayer->endTurn();
                        std::swap(currentPlayer, otherPlayer);
                        currentPlayer->startTurn();
                    }

					//Soldier üretme butonuna tıklandığında
                    else if (newSoldierBtn.isClicked(mousePos)) {
                        if (currentPlayer->spendGold(50)) {
                            for (int i = 0; i < 50; ++i) {
                                int x = rand() % gridSize;
                                int y = rand() % gridSize;

                                if (!grid.getCells()[x][y].hasObject()) {
                                    currentPlayer->addSoldier(Soldier(x, y, currentPlayer->getSoldierColor()));
                                    break;
                                }
                            }
                        }
                    }

                    else {
                        for (auto& s : currentPlayer->getSoldiers()) {
                            if (s.contains(mousePos))
                                s.toggleSelection(true);  // seçildi
                            else if (s.isSelected()) {
                                sf::Vector2i soldierPos = s.getGridPosition();
                                if (!s.hasMoved() && s.canMoveTo(soldierPos)) {
									//s.move(soldierPos);  // hareket et
                                    s.setTargetPosition(clickedGrid.x, clickedGrid.y);
                                    s.toggleSelection(false);  // seçimi kapat
                                }
                            }
                        }
                    }
                }
            }

        }

        // AI Hareketi
        if (currentPlayer->isAIControlled()) {
            for (auto& s : currentPlayer->getSoldiers()) {
                if (!s.isMovingNow()) {  // Hareket etmiyorsa yeni hedef ver
                    sf::Vector2i aiPos = s.getGridPosition();
                    sf::Vector2i target = player.getSoldiers()[0].getGridPosition();
                    sf::Vector2i dir((target.x > aiPos.x) ? 1 : (target.x < aiPos.x ? -1 : 0),
                        (target.y > aiPos.y) ? 1 : (target.y < aiPos.y ? -1 : 0));
                    s.setTargetPosition(aiPos.x + dir.x, aiPos.y + dir.y);
                }
            }

            enemy.produceSoldier(grid);  // AI asker üretimi
            currentPlayer->endTurn();
            std::swap(currentPlayer, otherPlayer);
            currentPlayer->startTurn();
        }

        // Movement Güncellemeleri
        for (auto& s : player.getSoldiers()) s.update(dt.asSeconds());
        for (auto& s : enemy.getSoldiers()) s.update(dt.asSeconds());

        // Arayüz
        goldText.setString("Gold: " + std::to_string(currentPlayer->getGold()));

        window.clear();
        grid.draw(window);

        for (auto& s : player.getSoldiers()) s.draw(window);
        for (auto& s : enemy.getSoldiers()) s.draw(window);

        if (!currentPlayer->isAIControlled()) {
            endTurnBtn.draw(window);
            newSoldierBtn.draw(window);
            window.draw(goldText);
        }

        window.display();
    }

    return 0;
}
