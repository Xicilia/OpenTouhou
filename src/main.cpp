#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "huinya ebanaya");
    sf::CircleShape shape(100.f);
    sf::Texture onscyweld;

    if (onscyweld.loadFromFile("src/snus.png")) {
        printf("loaded");
    }

    sf::Sprite sprite(onscyweld);

    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}
