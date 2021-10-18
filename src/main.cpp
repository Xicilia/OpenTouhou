#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

std::vector<std::pair<std::string,sf::Color>> Colors {std::make_pair("white",sf::Color(255,255,255,255))};

sf::Color GetColor(std::string ColorName) {
    for(std::pair<std::string,sf::Color> Color: Colors) {
        if (Color.first == ColorName) {
            return Color.second;
        }
    }
    return sf::Color(0,0,0,0); //return black if color does not exist
}

int main() {
    int WindowWidth = 900;
    int WindowHeight = 700;

    sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "OpenTouhou",sf::Style::Close);

    sf::Texture onscyweld;
    if (onscyweld.loadFromFile("src/snus.png")) {
        printf("loaded");
    }
    sf::Sprite snusprite(onscyweld);
    snusprite.scale(sf::Vector2f(2,5));

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
            } else if(event.type == sf::Event::TextEntered) {
                currKeyword += event.text.unicode;

                std::string word = std::string(currKeyword);
                std::cout<< word <<std::endl;                

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
        sf::Color white = GetColor("white");
        window.clear(white);

        //window.draw(sprite);
        if(snus){
            window.draw(snusprite);
        }
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