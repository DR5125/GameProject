#ifndef HEART_H
#define HEART_H

#pragma once
#include <SFML/Graphics.hpp>
#include "Reinforcements.h"

class Heart : public Reinforcements
{
public:
    // Konstruktor i destruktor
    Heart(const sf::Texture& texture, sf::Vector2f position);
    ~Heart();

    void Movement(sf::Time DeltaTime, sf::FloatRect bounds, sf::Vector2u window); // Metoda sterująca ruchem serca

private:
    sf::Texture texture;
    int frame = 0; // Numer bieżącej klatki animacji
    float frameTime = 1.0f / 10; // Czas trwania jednej klatki animacji
    float accumulatedtime = 0; // Całkowity czas dla animacji
    sf::Vector2f speed = sf::Vector2f(-100.f, 35.f); // Prędkość ruchu serca

    int random;
};

#endif // HEART_H
