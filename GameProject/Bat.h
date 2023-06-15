#ifndef BAT_H
#define BAT_H

#include "Enemy.h"
#include <random>
#include <ctime>

class Bat : public Enemy
{
    private:
        sf::Texture texture;
        int frame = 0;                // Numer bieżącej klatki animacji
        float frameTime = 1.0f / 10;  // Czas trwania jednej klatki animacji
        float accumulatedtime = 0;    // Całkowity czas dla animacji
        int random;
    public:
        // Konstruktor i destruktor
        Bat(const sf::Texture& texture, sf::Vector2f position);
        ~Bat();

        void Animate(sf::Time DeltaTime);                                             // Metoda animująca
        void Movement(sf::Time DeltaTime, sf::FloatRect bounds, sf::Vector2u window); // Metoda sterująca ruchem
};

#endif // BAT_H
