#include <SFML/Graphics.hpp>
#include "Hitbox.h"
#include "Board.h"

#ifndef ENTITY_H
#define ENTITY_H

class Entity {

    public:
        
        sf::Sprite GetSprite() { return Sprite; };
        //sf::FloatRect GetCollideBox() { return CollideBox; };
        Hitbox GetHitbox() { return MainHitbox; };
        CircleHitbox GetDetectHitbox() { return DetectHitbox; };

        Entity(sf::Texture texture);
        
        sf::Vector2f GetSpriteScale();
        void SetPos(sf::Vector2f pos);
        void SetHidePos(sf::Vector2f pos);
        //void SetPos();

        void IncreasePos(sf::Vector2f IncreasingValue);
        
        //sf::Vector2f Position;
        //sf::Vector2f CollideBoxSize;
    private:
        Hitbox MainHitbox;
        CircleHitbox DetectHitbox;
        float DetectHitboxScale;

        sf::Texture UsingTexture;
        sf::Sprite Sprite;
        //sf::FloatRect CollideBox;
        void DetectApplyPos();


};

class Player : public Entity {
    
    public:
        Player(sf::Texture texture,sf::Vector2f StartPosition,Board *board);

        void UpdatePosition(sf::Time ElapsedTime);
        Hitbox GetBoardHitbox() { return CurrentBoard->BoardHitBox; };

        void IncreaseSpeed(float value);
    private:
        float speed;

        Board *CurrentBoard;

        int VerticalMove;
        int HorizontalMove;
        bool IsShiftPressed;
};

#endif