#include "Player.h"

// Konstruktor
Player::Player() {}

// Destruktor
Player::~Player() {}

// Inicjalizacja gracza
void Player::Init(const sf::Texture& texture)
{
    setTexture(texture);
    setPosition(100.0f, 100.0f);
    setTextureRect(sf::IntRect(0, 0, 150, 150));
}

// Animowanie gracza
void Player::Animate(const sf::Time& elapsed)
{
    elapsedAccumulator += elapsed.asSeconds();

    // Sprawdzenie, czy wystarczył czas na zmianę klatki animacji
    if (elapsedAccumulator >= framePerSecond)
    {
        setTextureRect(sf::IntRect(frame * 150, 0, 150, 150));
        elapsedAccumulator = 0;
        frame++;
        frame %= 4;
    }
}

void Player::setLives(int i)
{//ustawienie poziomu ¿ycia
    lives += i;
}

void Player::setFuel(int i)
{//ustawienie poziomu paliwa
    fuel += i;
}


int Player::getLives()
{//pobranie poziomu ¿ycia
    return lives;
}

int Player::getFuel()
{//pobranie poziomu paliwa
    return fuel;
}

// Poruszanie się gracza
void Player::Movement(sf::Time elapsed, sf::Vector2f direction, sf::Vector2u window)
{
    // Obliczenie przemieszczenia gracza na podstawie czasu i kierunku
    move(direction.x * speed.x * elapsed.asSeconds(), direction.y * speed.y * elapsed.asSeconds());

    // Aktualizacja granic gracza na podstawie aktualnej pozycji
    sf::FloatRect playerBounds = getGlobalBounds();

    // Sprawdzenie granic okna i dostosowanie pozycji gracza, jeśli wykracza poza nie
    borders(playerBounds, window);

    // Zastosowanie grawitacji do ruchu gracza
    move(gravity.x, gravity.y * elapsed.asSeconds());
}

// Sprawdzanie granic okna i dostosowywanie pozycji gracza
void Player::borders(sf::FloatRect bounds, sf::Vector2u window)
{
    if (bounds.left <= 0)
    {
        setPosition(1, getPosition().y);
    }
    else if (bounds.left + bounds.width >= window.x)
    {
        setPosition(window.x - bounds.width - 1, getPosition().y);
    }

    if (bounds.top <= 0)
    {
        setPosition(getPosition().x, 1);
    }
    else if (bounds.top + bounds.height >= (window.y - 100))
    {
        setPosition(getPosition().x, window.y - bounds.height -
                    101);
    }
}

void Player::setScore(int i)
{//ustawienie liczby punktów
    score += i;
}

int Player::getScore()
{//pobranie iloœci punktów
    return score;
}

