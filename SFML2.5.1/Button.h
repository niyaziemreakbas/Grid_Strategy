#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text);
    void draw(sf::RenderWindow& window);
    bool isClicked(sf::Vector2f point) const;

private:
    sf::RectangleShape shape;
    sf::Text buttonText;
    sf::Font font;
};
