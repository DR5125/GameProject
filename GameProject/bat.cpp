#include "Bat.h"

Bat::Bat(const sf::Texture& texture, sf::Vector2f position)
{	//konstruktor inijcuj¹cy ziarno dla losowoœci oraz teksturê i pozycjê
    srand(time(NULL));
    setTexture(texture);
    setTextureRect(sf::IntRect(0, 0, 75, 75));
    setPosition(position);
    random = rand() % 100;
}

Bat::~Bat()
{///destruktor
}

void Bat::Animate(sf::Time DeltaTime)
{	//animacja dla ptaka
    accumulatedtime += DeltaTime.asSeconds();
    if (accumulatedtime >= frameTime)
    {
        frame++;
        frame %= 4;
        int frameWidth = 300 / 4; // Szerokość pojedynczej klatki (100 pikseli)
        int frameHeight = 75; // Wysokość klatki (150 pikseli)

        setTextureRect(sf::IntRect(frame * frameWidth, 0, frameWidth, frameHeight));
        accumulatedtime = 0;

    }
}

void Bat::Movement(sf::Time DeltaTime, sf::FloatRect bounds, sf::Vector2u window)
{	//ruch
    move((-50 - (random%50)) * DeltaTime.asSeconds(), ((50- random))*DeltaTime.asSeconds());
    borders(bounds, window);
}
