#include "Fuel.h"
#include <ctime>

Fuel::Fuel(const sf::Texture& texture, sf::Vector2f position)
{
    srand(time(NULL));
    setTexture(texture);
    setPosition(position);
    random = 50 + rand () %  100;
}

Fuel::~Fuel() {}

void Fuel::Movement(sf::Time DeltaTime, sf::FloatRect bounds, sf::Vector2u window)
{
    move(0, ((random)) * DeltaTime.asSeconds()); // Poruszanie obiektem "Fuel" wzdłuż osi y
    borders(bounds, window);
}
