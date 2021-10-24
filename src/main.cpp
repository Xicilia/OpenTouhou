#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "Entity.h"
#include "Board.h"
#include "Hitbox.h"

struct Texture {
    sf::Texture texture;
    std::string textureId;
};

std::vector<std::pair<std::string,sf::Color>> Colors {std::make_pair("white",sf::Color(255,255,255,255))};

std::vector<std::pair<std::string,std::string>> texturesToInit{ std::make_pair("snus","src/data/snus.png"),std::make_pair("player","src/data/snus.png") };

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

int main() {
    int WindowWidth = 900;
    int WindowHeight = 700;

    sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "OpenTouhou", sf::Style::Close);
    std::vector<Texture> usingTextures = initTextures();

    sf::Texture snustexture = getTextureById(usingTextures, "snus");
    sf::Sprite snusprite(snustexture);
    snusprite.scale(sf::Vector2f(1.8,10));

    Board CurrentBoard(sf::Vector2f(20,20),sf::Vector2f(520,650));

    sf::Texture playerTexture = getTextureById(usingTextures, "player");
    Player player(playerTexture,sf::Vector2f(250,250),&CurrentBoard);

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

        player.UpdatePosition(elapsedTime);

        sf::Color white = GetColor("white");
        window.clear(white);

        // drawing
        if (snus) {
            window.draw(snusprite);
        }

        window.draw(CurrentBoard.BoardShape);
        sf::Sprite PlayerSprite = player.GetSprite();
        window.draw(PlayerSprite);

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

            //drawing player hitbox
            sf::RectangleShape PlayerHitbox = CreateShapeFromHitbox(player.GetHitbox(),sf::Color::Red);
            sf::RectangleShape PlayerDetectHitbox = CreateShapeFromHitbox(player.GetDetectHitbox(),sf::Color::Black);
            window.draw(PlayerHitbox);
            window.draw(PlayerDetectHitbox);
        }
        window.display();
    } 
    return 0;
}