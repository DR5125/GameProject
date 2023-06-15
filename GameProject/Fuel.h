#ifndef FUEL_H
#define FUEL_H

#include <SFML/Graphics.hpp>
#include "Reinforcements.h"

class Fuel : public Reinforcements
{
public:
    // Konstruktor i destruktor
    Fuel(const sf::Texture& texture, sf::Vector2f position);
    ~Fuel();

    void Movement(sf::Time DeltaTime, sf::FloatRect bounds, sf::Vector2u window); // Metoda sterująca ruchem paliwa

private:
    int random;
};

#endif // FUEL_H
