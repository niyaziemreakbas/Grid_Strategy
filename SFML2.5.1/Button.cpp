#include "Button.h"

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text) {
    shape.setSize(size);
    shape.setFillColor(sf::Color(100, 100, 100));
    shape.setPosition(position);

    font.loadFromFile("C:/Windows/Fonts/arial.ttf"); // Windows için örnek

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(18);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(position + sf::Vector2f(10, 5));
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(buttonText);
}

bool Button::isClicked(sf::Vector2f point) const {
    return shape.getGlobalBounds().contains(point);
}
