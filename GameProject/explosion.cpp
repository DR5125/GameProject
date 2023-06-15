#include "Explosion.h"

Explosion::Explosion(const sf::Texture& texture, const sf::Vector2f& playerPosition)
{
    setTexture(texture);
    setPosition(playerPosition);
    setTextureRect(sf::IntRect(0,0, 100, 100));
}

Explosion::~Explosion(){}

void Explosion::Animate(sf::Time DeltaTime)
{
    //animacja
    accumulatedtime += DeltaTime.asSeconds();
    if (accumulatedtime >= frameTime)
    {
        frame++;
        frame %= 4;
        //std::cout << Del << std::endl;
        int frameWidth = 600 / 6 ; // Szerokość pojedynczej klatki
        int frameHeight = 100; // Wysokość klatki (150 pikseli)

        setTextureRect(sf::IntRect(frame * frameWidth, 0, frameWidth, frameHeight));

        accumulatedtime = 0;
    }
}
