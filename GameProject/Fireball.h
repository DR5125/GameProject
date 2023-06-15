#ifndef FIREBALL_H
#define FIREBALL_H

#include <SFML/Graphics.hpp>

class Fireball:public sf::Sprite
{
    public:
        Fireball(const sf::Texture& texture, const sf::Vector2f& playerPosition);
        ~Fireball();

        void shot(sf::Time deltaTime); // Metoda odpowiadająca za strzał pocisku
        void Animate(sf::Time DeltaTime); // Animacja
    private:
        sf::Texture texture;
        sf::Vector2f speed = sf::Vector2f(100.f, 70.f);
        int frame = 0; // Numer aktualnej klatki animacji
        float frameTime = 1.0f / 10; // Czas trwania jednej klatki animacji
        float accumulatedtime = 0; // całkowity czas dla animacji
};

#endif // FIREBALL_H
