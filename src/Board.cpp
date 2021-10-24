#include "Board.h"
#include <SFML/Graphics.hpp>


Board::Board(sf::Vector2f Position, sf::Vector2f Size){
    BoardHitBox = Hitbox(Size,Position);

    BoardShape.setSize(Size);
    BoardShape.setPosition(Position);

    BoardShape.setOutlineColor(sf::Color::Black);
    BoardShape.setOutlineThickness(2);
}