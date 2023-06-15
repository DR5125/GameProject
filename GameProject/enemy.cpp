#include "Enemy.h"

Enemy::Enemy() {}

Enemy::~Enemy() {}

void Enemy::borders(sf::FloatRect bounds, sf::Vector2u window)
{
    if (bounds.top <= 0) // Jeżeli górna krawędź obiektu wychodzi poza górną krawędź ekranu
    {
        setPosition(getPosition().x, window.y - 113); // Przeniesienie obiektu na dolną krawędź ekranu
    }
    else if (bounds.top + bounds.height >= window.y) // Jeżeli dolna krawędź obiektu wychodzi poza dolną krawędź ekranu
    {
        setPosition(getPosition().x, 1); // Przeniesienie obiektu na górną krawędź ekranu
    }
}
