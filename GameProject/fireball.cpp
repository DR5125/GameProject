#include "Fireball.h"

Fireball::Fireball(const sf::Texture& texture, const sf::Vector2f& playerPosition)
{
    setTexture(texture);
    setPosition(playerPosition);
    setTextureRect(sf::IntRect(0, 0, 57, 23));
}

Fireball::~Fireball() {}

void Fireball::shot(sf::Time deltaTime)
{
    move(200.f * deltaTime.asSeconds(), 0); // Poruszanie fireball'em wzdłuż osi x
}

void Fireball::Animate(sf::Time DeltaTime)
{
    accumulatedtime += DeltaTime.asSeconds();
    if (accumulatedtime >= frameTime)
    {
        frame++;
        frame %= 4; // Ograniczenie numeru klatki animacji do zakresu 0-3
        int frameWidth = 400 / 7; // Szerokość pojedynczej klatki animacji
        int frameHeight = 23; // Wysokość klatki animacji

        setTextureRect(sf::IntRect(frame * frameWidth, 0, frameWidth, frameHeight));

        accumulatedtime = 0;
    }
}
