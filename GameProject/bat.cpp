#include "Bat.h"

Bat::Bat(const sf::Texture& texture, sf::Vector2f position)
{
    srand(time(NULL)); // Inicjalizacja generatora liczb losowych
    setTexture(texture);
    setTextureRect(sf::IntRect(0, 0, 75, 75));
    setPosition(position);
    random = rand() % 100; // Wygenerowanie losowej wartości dla "random" od 0 do 99
}

Bat::~Bat() {}

void Bat::Animate(sf::Time DeltaTime)
{
    accumulatedtime += DeltaTime.asSeconds();
    if (accumulatedtime >= frameTime)
    {
        frame++;
        frame %= 4; // Ograniczenie numeru klatki animacji do zakresu 0-3
        int frameWidth = 300 / 4; // Szerokość pojedynczej klatki animacji
        int frameHeight = 75; // Wysokość klatki animacji
        setTextureRect(sf::IntRect(frame * frameWidth, 0, frameWidth, frameHeight));
        accumulatedtime = 0;
    }
}

void Bat::Movement(sf::Time DeltaTime, sf::FloatRect bounds, sf::Vector2u window)
{
    move((-50 - (random % 50)) * DeltaTime.asSeconds(), ((50 - random)) * DeltaTime.asSeconds());
    borders(bounds, window); // Sprawdzenie i obsługa wyjścia obiektu poza ekran
}
