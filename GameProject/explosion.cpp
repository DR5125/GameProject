#include "Explosion.h"

Explosion::Explosion(const sf::Texture& texture, const sf::Vector2f& enemyPosition)
{

    setTexture(texture);
    setPosition(enemyPosition);
    setTextureRect(sf::IntRect(0, 0, 100, 100));
}

Explosion::~Explosion() {}

void Explosion::Animate(sf::Time DeltaTime)
{
    accumulatedtime += DeltaTime.asSeconds();
    if (accumulatedtime >= frameTime)
    {
        frame++;
        frame %= 4; // Ograniczenie numeru klatki animacji do zakresu 0-3
        int frameWidth = 600 / 6; // Szerokość pojedynczej klatki animacji
        int frameHeight = 100; // Wysokość klatki animacji

        setTextureRect(sf::IntRect(frame * frameWidth, 0, frameWidth, frameHeight));

        accumulatedtime = 0;
    }
}

bool Explosion::getLiveTime(sf::Time DeltaTime)
{
    liveTime += DeltaTime;
    if (liveTime.asSeconds() > 0.4 )
    {
        return true;
    }
    return false;
}
