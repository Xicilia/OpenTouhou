#include <SFML/Graphics.hpp>
#include "Hitbox.h"

#ifndef BOARD_H
#define BOARD_H

class Board {
    public:
        Hitbox BoardHitBox;

        Board() {};
        Board(sf::Vector2f Size, sf::Vector2f Position);

        sf::RectangleShape BoardShape;

};

#endif