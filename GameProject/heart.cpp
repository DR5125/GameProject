#include "Heart.h"

Heart::Heart(const sf::Texture& texture, sf::Vector2f position)
{
    // Konstruktor ustawiający teksturę i pozycję obiektu
    srand(time(NULL));
    setTexture(texture);
    setPosition(position);
    random = rand() % 100;
}

Heart::~Heart() {}

void Heart::Movement(sf::Time DeltaTime, sf::FloatRect bounds, sf::Vector2u window)
{
    // Ruch obiektu typu serce
    move(0, ((- random)) * DeltaTime.asSeconds()); // Poruszanie obiektem w dół
    borders(bounds, window);
}
