#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy : public sf::Sprite
{
private:
    sf::Texture texture;
    sf::Vector2f speed = sf::Vector2f(100.f, 70.f);
    int frame = 0;                                   // Numer aktualnej klatki animacji
    float frameTime = 1.0f / 10;                     // Czas trwania jednej klatki animacji
    float accumulate = 0;                            // Całkowity czas dla animacji

public:
    // Konstruktor i destruktor
    Enemy();
    ~Enemy();

    virtual void borders(sf::FloatRect bounds, sf::Vector2u window); // Metoda sprawdzająca czy obiekty wychodzą poza ekran i przenosząca je
};

#endif // ENEMY_H
