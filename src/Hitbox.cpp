#include "Hitbox.h"
#include <SFML/Graphics.hpp>


Hitbox::Hitbox(sf::Vector2f StartSize) {
    Position = sf::Vector2f(0,0);
    Size = StartSize;
}

Hitbox::Hitbox(sf::Vector2f StartSize,sf::Vector2f StartPosition) {
    Position = StartPosition;
    Size = StartSize;
}

sf::RectangleShape CreateShapeFromHitbox(Hitbox UsingHitbox,sf::Color UsingColor) {
    sf::RectangleShape shape;
    shape.setSize(UsingHitbox.Size);
    shape.setPosition(UsingHitbox.Position);
    shape.setOutlineColor(UsingColor);
    shape.setOutlineThickness(2);
    shape.setFillColor(sf::Color(0,0,0,0));
    return shape;
}