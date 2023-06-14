#include "Helicopter.h"
#include <random>
#include <ctime>


Helicopter::Helicopter(const sf::Texture& texture, sf::Vector2f position)
{	//inicjalizacja ziarna dla losowoœci i konstruktor obiektu
    srand(time(NULL));
    setTexture(texture);
    setTextureRect(sf::IntRect(0, 0, 113, 113));
    setPosition(position);
}

Helicopter::~Helicopter()
{//destruktor
}

void Helicopter::Animate(sf::Time DeltaTime)
{	//animacja helikoptera
    accumulatedtime += DeltaTime.asSeconds();
    if (accumulatedtime >= frameTime)
    {
        frame++;
        frame %= 4;
        //std::cout << Del << std::endl;
        int frameWidth = 450 / 4; // Szerokość pojedynczej klatki (150 pikseli)
        int frameHeight = 113; // Wysokość klatki (150 pikseli)

        setTextureRect(sf::IntRect(frame * frameWidth, 0, frameWidth, frameHeight));

        accumulatedtime = 0;
    }
}

void Helicopter::Movement(sf::Time DeltaTime, sf::FloatRect bounds, sf::Vector2u window,float directiony)
{	//poruszanie siê helikoptera w zale¿noœci od po³o¿enia gracza, w górê lub dó³
    if (directiony > (getPosition().y-30))
    {
        move(speed.x * DeltaTime.asSeconds(), speed.y * DeltaTime.asSeconds());
    }
    else if (directiony <= (getPosition().y-30))
    {
        move(speed.x * DeltaTime.asSeconds(), speed.y * DeltaTime.asSeconds() * (-1));
    }
    this->borders( bounds,window);//odwo³anie do funkcji klasy Enemy
}

void Helicopter::setlives()
{	//zmienianie poziomu ¿ycia
    lives -= 1;
}

int Helicopter::getlives()
{	//pobieranie poziomu ¿ycia
    return lives;
}
