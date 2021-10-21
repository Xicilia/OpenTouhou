#include <SFML/Graphics.hpp>

class Entity {

    public:
        
        sf::Sprite GetSprite() { return Sprite; };
        sf::FloatRect GetCollideBox() { return CollideBox; };

        Entity(sf::Texture texture);
        
        sf::Vector2f GetSpriteScale();
        void SetPos(sf::Vector2f pos);
        void SetPos();

        sf::Vector2f Position;
        sf::Vector2f CollideBoxSize;
    private:

        sf::Texture UsingTexture;
        sf::Sprite Sprite;
        sf::FloatRect CollideBox;


};

class Player : public Entity {
    
    public:
        Player(sf::Texture texture);

        void UpdatePosition(sf::Time ElapsedTime);
    private:
        float speed;

        int VerticalMove;
        int HorizontalMove;
        bool IsShiftPressed;
};