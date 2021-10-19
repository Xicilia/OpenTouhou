#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#define PLAYERWIDTHCONSTANT 100.0
#define PLAYERHEIGHTCONSTANT 100.0

class Player {

    public:
        float verticalMove;
        float horizontalMove;
        bool isShiftPressed;
        Player(sf::Texture PlayerTexture) {
            texture = PlayerTexture;

            speed = 0.1f;
            playerSprite = sf::Sprite(texture);
            //playerSprite.resize(sf::Vector2f(PLAYERWIDTHCONSTANT,PLAYERHEIGHTCONSTANT));
            float scaleWidth = PLAYERWIDTHCONSTANT / texture.getSize().x;
            float scaleHeight = PLAYERHEIGHTCONSTANT / texture.getSize().y;
            std::cout << "scaling player sprite width with " << scaleWidth << " scale" << std::endl;
            std::cout << "scaling player sprite height with " << scaleHeight << " scale" << std::endl;
            playerSprite.scale(sf::Vector2f(scaleWidth, scaleHeight));

            verticalMove = 0;
            horizontalMove = 0;

        }

        sf::Vector2f getPlayerPos() {
            return playerSprite.getPosition();
        }
        sf::Vector2f getPlayerSize() {
            sf::Vector2u textureSize = texture.getSize();
            sf::Vector2f spriteScale = playerSprite.getScale();

            return sf::Vector2f(textureSize.x * spriteScale.x, textureSize.y * spriteScale.y);
        }
        void setPos(sf::Vector2f pos) {
            playerSprite.setPosition(pos);
        }
        sf::Sprite getCurrentSpriteToDraw() {
            return playerSprite;
        }
        void move() {

            float currSpeed;
            if (isShiftPressed) {
                currSpeed = speed * 0.5;
            }
            else {
                currSpeed = speed;
            }

            if (verticalMove) {
                playerSprite.move(0, currSpeed * verticalMove);
            }
            if (horizontalMove) {
                playerSprite.move(currSpeed * horizontalMove, 0);
            }

        }
    private:
        sf::Texture texture;
        sf::Sprite playerSprite;
        sf::IntRect playerRect;

        float speed;
};
struct Texture {
    sf::Texture texture;
    std::string textureId;
};

struct Board {
  
    float x;
    float y;
    float width;
    float height;

};



std::vector<std::pair<std::string,sf::Color>> Colors {std::make_pair("white",sf::Color(255,255,255,255))};

std::vector<std::pair<std::string,std::string>> texturesToInit{ std::make_pair("snus","src/data/snus.png"),std::make_pair("player","src/data/table.jpg") };

std::vector<Texture> initTextures() {
    
    std::vector<Texture> textures;

    for (std::pair<std::string, std::string> notInitedTexture : texturesToInit) {
        sf::Texture textureSRC;

        
        if (!textureSRC.loadFromFile(notInitedTexture.second)) {
            continue;
        }

        Texture currentTexture{ textureSRC,notInitedTexture.first };
        textures.push_back(currentTexture);
    }

    return textures;

}

sf::Color GetColor(std::string ColorName) {
    for(std::pair<std::string,sf::Color> Color: Colors) {
        if (Color.first == ColorName) {
            return Color.second;
        }
    }
    return sf::Color(0,0,0,0); //return black if color does not exist
}

sf::Texture getTextureById(std::vector<Texture>textureList, std::string Id) {
    
    for (Texture currentTexture : textureList) {
        if (currentTexture.textureId == Id) {
            return currentTexture.texture;
        }
    }
    Texture NaNtexture;
    NaNtexture.textureId = "NaN";
    return NaNtexture.texture;

}


void UpdateMovement(&player) {
    player.verticalMove = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) + -sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    player.horizontalMove = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) + -sf::Keyboard::isKeyPressed(sf::Keyboard::Left);

    player.isShiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
}

int main() {
    int WindowWidth = 900;
    int WindowHeight = 700;

    sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "OpenTouhou", sf::Style::Close);
    std::vector<Texture> usingTextures = initTextures();

    sf::Texture snustexture = getTextureById(usingTextures, "snus");
    sf::Sprite snusprite(snustexture);
    snusprite.scale(sf::Vector2f(1.8,10));

    sf::Texture playerTexture = getTextureById(usingTextures, "player");
    Player player(playerTexture);
    player.horizontalMove = 0;
    player.verticalMove = 0;
    player.isShiftPressed = false;
    sf::Vector2f playerSize = player.getPlayerSize();

    Board board{ 20.0,20.0,520.0,650.0 };
    sf::RectangleShape boardShape;
    boardShape.setSize(sf::Vector2f(board.width, board.height));
    boardShape.setPosition(sf::Vector2f(board.x, board.y));
    boardShape.setFillColor(sf::Color(0, 0, 0, 0));
    boardShape.setOutlineColor(sf::Color::Black);
    boardShape.setOutlineThickness(2);

    sf::Clock clock;

    bool DebugMode = false;
    sf::Font DebugFont;
    if(!DebugFont.loadFromFile("src/fonts/debug.ttf")) {
        return 0;
    }

    bool snus = false;
    sf::String currKeyword;
    while (window.isOpen()) {
        sf::Time elapsedTime = clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::O){
                    DebugMode = !DebugMode;
                    printf("Debug mode value have been changed");
                }
                else if (event.key.code == sf::Keyboard::Up or event.key.code == sf::Keyboard::Down or event.key.code == sf::Keyboard::Right or event.key.code == sf::Keyboard::Left or event.key.code == sf::Keyboard::LShift) {
                    UpdateMovement(&player);
                }
            }
            else if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Up or event.key.code == sf::Keyboard::Down or event.key.code == sf::Keyboard::Right or event.key.code == sf::Keyboard::Left or event.key.code == sf::Keyboard::LShift) {
                    UpdateMovement(&player);
                }
            }
            else if(event.type == sf::Event::TextEntered) {
                currKeyword += event.text.unicode;

                std::string word = std::string(currKeyword);
                //std::cout<< word <<std::endl;                

                if(currKeyword.find("givemesnus") != sf::String::InvalidPos and !snus) {
                    printf("snus set to true");
                    snus = true;
                    window.setTitle("OpenSnushou");
                }

                if (currKeyword.getSize() >= 20) {
                    currKeyword.clear();
                }

                

            }
        }
        player.move();

        sf::Vector2f currentPos = player.getPlayerPos();
        
        if (currentPos.x >= board.width - playerSize.x) {
            currentPos.x = board.width - playerSize.x - 1;
            player.horizontalMove = 0;
            player.setPos(currentPos);
        }
        else if (currentPos.x <= board.x) {
            currentPos.x = board.x + 1;
            player.horizontalMove = 0;
            player.setPos(currentPos);
        }
        if (currentPos.y >= board.height - playerSize.y) {
            currentPos.y = board.height - playerSize.y - 1;
            player.verticalMove = 0;
            player.setPos(currentPos);
        }
        else if (currentPos.y <= board.y) {
            currentPos.y = board.y + 1;
            player.verticalMove = 0;
            player.setPos(currentPos);
        }


        sf::Color white = GetColor("white");
        window.clear(white);

        // drawing
        if (snus) {
            window.draw(snusprite);
        }

        window.draw(boardShape);
        window.draw(player.getCurrentSpriteToDraw());

        if (DebugMode) {
            int fontsize = 18;
            sf::Vector2u TextSpriteSize = DebugFont.getTexture(fontsize).getSize();

            sf::Text elapsedTimeText;

            elapsedTimeText.setFont(DebugFont);
            elapsedTimeText.setString("time elapsed: " + std::to_string(elapsedTime.asMicroseconds()));
            elapsedTimeText.setCharacterSize(fontsize);
            elapsedTimeText.setFillColor(sf::Color::Black);
            elapsedTimeText.setPosition(sf::Vector2f(WindowWidth-TextSpriteSize.x * 2,WindowHeight-TextSpriteSize.y));

            window.draw(elapsedTimeText);
        }
        window.display();
    } 
    return 0;
}