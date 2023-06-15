#include "Reinforcements.h"

Reinforcements::Reinforcements() {}

Reinforcements::~Reinforcements() {}

void Reinforcements::borders(sf::FloatRect bounds, sf::Vector2u window)
{
    // Obsługa granic dla obiektu wzmacniającego
    if (bounds.top <= 0)
    {
        setPosition(getPosition().x, window.y - 113); // Przesunięcie obiektu na dolną krawędź ekranu
    }
    else if (bounds.top + bounds.height >= window.y)
    {
        setPosition(getPosition().x, 1); // Przesunięcie obiektu na górną krawędź ekranu
    }
}
