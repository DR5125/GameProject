#ifndef HELICOPTER_H
#define HELICOPTER_H

#include "Enemy.h"

class Helicopter : public Enemy
{
private:
    sf::Texture texture;
    int frame = 0; // Numer bieżącej klatki animacji
    float frameTime = 1.0f / 10; // Czas trwania jednej klatki animacji
    float accumulatedtime = 0; // Całkowity czas dla animacji
    sf::Vector2f speed = sf::Vector2f(-100.f, 35.f); // Prędkość helikoptera
    int lives = 2; // Liczba żyć helikoptera

public:
    // Konstruktor i destruktor
    Helicopter(const sf::Texture& texture, sf::Vector2f position);
    ~Helicopter();

    void Animate(sf::Time DeltaTime); // Metoda animacji helikoptera
    void Movement(sf::Time DeltaTime, sf::FloatRect bounds, sf::Vector2u window, float directiony); // Metoda sterująca ruchem helikoptera w kierunku gracza
    void setLives(); // Metoda zmieniająca liczbę żyć helikoptera
    int getLives(); // Metoda pobierająca liczbę żyć helikoptera
};

#endif // HELICOPTER_H
