#include <SFML/Graphics.hpp>

#ifndef HITBOX_H
#define HITBOX_H

class Hitbox {
    
    public:
        sf::Vector2f Position;
        sf::Vector2f Size;

        Hitbox() {};

        Hitbox(sf::Vector2f StartSize);
        Hitbox(sf::Vector2f StartSize,sf::Vector2f StartPosition);

        friend sf::RectangleShape CreateShapeFromHitbox(Hitbox UsingHitbox,sf::Color UsingColor);

        //bool CollisionWith(Hitbox TestedHitbox); //later
        //bool IsInside(Hitbox TestedHitbox); //later

};

#endif