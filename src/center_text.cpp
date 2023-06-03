/*
** EPITECH PROJECT, 2023
** center_text
** File description:
** center text
*/

#include "pokemon_cpp.hpp"

void centerText(sf::Text& text, const sf::RectangleShape& button)
{
    sf::FloatRect textBounds = text.getLocalBounds();
    float offsetX = button.getPosition().x + (button.getSize().x - textBounds.width) / 2.0f;
    float offsetY = button.getPosition().y + (button.getSize().y - textBounds.height) / 2.0f;
    text.setPosition(offsetX, offsetY);
}
