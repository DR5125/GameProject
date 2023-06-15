#include "Helicopter.h"
#include <random>
#include <ctime>

Helicopter::Helicopter(const sf::Texture& texture, sf::Vector2f position)
{
    // Inicjalizacja ziarna dla losowości i konstruktor obiektu
    srand(time(NULL));
    setTexture(texture);
    setTextureRect(sf::IntRect(0, 0, 113, 113));
    setPosition(position);
}

Helicopter::~Helicopter()
{
    // Destruktor
}

void Helicopter::Animate(sf::Time DeltaTime)
{
    // Animacja helikoptera
    accumulatedtime += DeltaTime.asSeconds();
    if (accumulatedtime >= frameTime)
    {
        frame++;
        frame %= 4;
        int frameWidth = 450 / 4; // Szerokość pojedynczej klatki (113 pikseli)
        int frameHeight = 113; // Wysokość klatki (113 pikseli)

        setTextureRect(sf::IntRect(frame * frameWidth, 0, frameWidth, frameHeight));

        accumulatedtime = 0;
    }
}

void Helicopter::Movement(sf::Time DeltaTime, sf::FloatRect bounds, sf::Vector2u window, float directiony)
{
    // Poruszanie się helikoptera w zależności od położenia gracza, w górę lub w dół
    if (directiony > (getPosition().y - 30))
    {
        move(speed.x * DeltaTime.asSeconds(), speed.y * DeltaTime.asSeconds());
    }
    else if (directiony <= (getPosition().y - 30))
    {
        move(speed.x * DeltaTime.asSeconds(), speed.y * DeltaTime.asSeconds() * (-1));
    }
    borders(bounds, window); // Odwołanie do funkcji klasy Enemy
}

void Helicopter::setLives()
{
    // Zmienianie poziomu życia
    lives -= 1;
}

int Helicopter::getLives()
{
    // Pobieranie poziomu życia
    return lives;
}
