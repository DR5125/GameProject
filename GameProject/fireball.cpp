#include "Fireball.h"

Fireball::Fireball(const sf::Texture& texture, const sf::Vector2f& playerPosition)
{
    setTexture(texture);
    setPosition(playerPosition);
    setTextureRect(sf::IntRect(0,0, 57, 23));
}

Fireball::~Fireball(){}

void Fireball::shot(sf::Time deltaTime)
{
    move(200.f * deltaTime.asSeconds(), 0); // poruszanie fireball'em
}
void Fireball::Animate(sf::Time DeltaTime)
{	//animacja helikoptera
    accumulatedtime += DeltaTime.asSeconds();
    if (accumulatedtime >= frameTime)
    {
        frame++;
        frame %= 4;
        //std::cout << Del << std::endl;
        int frameWidth = 400 / 7 ; // Szerokość pojedynczej klatki (150 pikseli)
        int frameHeight = 23; // Wysokość klatki (150 pikseli)

        setTextureRect(sf::IntRect(frame * frameWidth, 0, frameWidth, frameHeight));

        accumulatedtime = 0;
    }
}
