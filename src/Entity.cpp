#include "Entity.h"
#include <SFML/Graphics.hpp>

#define PLAYERWIDTHCONSTANT 100.0
#define PLAYERHEIGHTCONSTANT 100.0

Entity::Entity(sf::Texture texture) {

    UsingTexture = texture;

    Sprite = sf::Sprite(UsingTexture);

    // scaling sprite
    sf::Vector2u TextureSize = UsingTexture.getSize();
    float WidthScale = PLAYERWIDTHCONSTANT / TextureSize.x;
    float HeightScale = PLAYERHEIGHTCONSTANT / TextureSize.y;
    Sprite.setScale(sf::Vector2f(WidthScale,HeightScale));

    //creating collidebox from sprite
    sf::Vector2f Position = sf::Vector2f(0,0);
    sf::Vector2f CollideBoxSize = sf::Vector2f(TextureSize.x * WidthScale, TextureSize.y * HeightScale);
    CollideBox = sf::FloatRect(Position,CollideBoxSize);

}

sf::Vector2f Entity::GetSpriteScale() {
    return Sprite.getScale();
}
void Entity::SetPos(sf::Vector2f pos) {
    Position.x = pos.x;
    Position.y = pos.y;

    CollideBox.left = Position.x;
    CollideBox.top = Position.y;

    Sprite.setPosition(sf::Vector2f(CollideBox.left, CollideBox.top));
}
void Entity::SetPos() {
    CollideBox.left = Position.x;
    CollideBox.top = Position.y;

    Sprite.setPosition(sf::Vector2f(CollideBox.left, CollideBox.top));
}

Player::Player(sf::Texture texture): Entity::Entity(texture) {
    VerticalMove = 0;
    HorizontalMove = 0;
    IsShiftPressed = false;

    speed = 1.f;

}

void Player::UpdatePosition(sf::Time ElapsedTime){
    VerticalMove = -sf::Keyboard::isKeyPressed(sf::Keyboard::Up) + sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    HorizontalMove = -sf::Keyboard::isKeyPressed(sf::Keyboard::Left) + sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    IsShiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

    float CurrentSpeed;

    if (IsShiftPressed) {
        CurrentSpeed = speed  * 0.5;
    } else {
        CurrentSpeed = speed;
    }

    if (VerticalMove) {
        Position.y += CurrentSpeed * ElapsedTime.asMilliseconds() * VerticalMove; 
    }
    if(HorizontalMove) {
        Position.x += CurrentSpeed * ElapsedTime.asMilliseconds() * HorizontalMove;
    }
    SetPos();
}