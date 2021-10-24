#include "Entity.h"
#include "Board.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "cmath"

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

    //creating main hitbox from sprite
    sf::Vector2f HitboxSize = sf::Vector2f(TextureSize.x * WidthScale, TextureSize.y * HeightScale);
    MainHitbox = Hitbox(HitboxSize);

    //creating hitbox for missles collide
    sf::Vector2f DetectHitboxSize = sf::Vector2f(HitboxSize.x / 3, HitboxSize.y / 3);
    sf::Vector2f DetectHitboxPosition = sf::Vector2f(HitboxSize.x / 2,HitboxSize.y / 2);
    DetectHitbox = Hitbox(DetectHitboxSize,DetectHitboxPosition);

}

sf::Vector2f Entity::GetSpriteScale() {
    return Sprite.getScale();
}

void Entity::DetectApplyPos() {
    //DetectHitbox.Position = MainHitbox.Position;
    DetectHitbox.Position = sf::Vector2f(MainHitbox.Position.x + MainHitbox.Size.x / 3, 
    MainHitbox.Position.y + MainHitbox.Size.y / 3);
}

void Entity::SetPos(sf::Vector2f pos) {
    MainHitbox.Position.x = pos.x;
    MainHitbox.Position.y = pos.y;
    DetectApplyPos();

    Sprite.setPosition(sf::Vector2f(MainHitbox.Position.x, MainHitbox.Position.y));
}
void Entity::IncreasePos(sf::Vector2f IncreasingValue)  {
    MainHitbox.Position.x += IncreasingValue.x;
    MainHitbox.Position.y += IncreasingValue.y;
    DetectApplyPos();

    Sprite.setPosition(sf::Vector2f(MainHitbox.Position.x, MainHitbox.Position.y)); 
}

void Entity::SetHidePos(sf::Vector2f Pos){
    MainHitbox.Position.x = Pos.x;
    MainHitbox.Position.y = Pos.y;
    DetectApplyPos();
}

Player::Player(sf::Texture texture,sf::Vector2f StartPosition,Board *board): Entity::Entity(texture) {
    VerticalMove = 0;
    HorizontalMove = 0;
    IsShiftPressed = false;

    speed = 1.f;

    SetPos(StartPosition);

    CurrentBoard = board;

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

    float Increase = CurrentSpeed * ElapsedTime.asMilliseconds();

    Hitbox PlayerHitbox = GetHitbox();
    Hitbox BoardHitBox = GetBoardHitbox();

    if(PlayerHitbox.Position.x + Increase > BoardHitBox.Size.x - PlayerHitbox.Size.x + BoardHitBox.Position.x) {
        if (HorizontalMove == 1) {
            HorizontalMove = 0;
        }
    } else if(PlayerHitbox.Position.x - Increase < BoardHitBox.Position.x) {
        if (HorizontalMove == -1) {
            HorizontalMove = 0;
        }
    }
    if(PlayerHitbox.Position.y + Increase > BoardHitBox.Size.y - PlayerHitbox.Size.y + BoardHitBox.Position.y) {
        if (VerticalMove == 1){
            VerticalMove = 0;
        }
    } else if(PlayerHitbox.Position.y - Increase < BoardHitBox.Position.y) {
        if (VerticalMove == -1) {
            VerticalMove = 0;
        }
    }

    IncreasePos(sf::Vector2f(Increase * HorizontalMove,Increase * VerticalMove));

}