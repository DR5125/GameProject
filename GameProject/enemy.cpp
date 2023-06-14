#include "Enemy.h"

Enemy::Enemy() {}

Enemy::~Enemy() {}

void Enemy::borders(sf::FloatRect bounds, sf::Vector2u window)
{
    if (bounds.top <= 0)
    {
        setPosition(getPosition().x, window.y - 130);
    }
    else if (bounds.top + bounds.height >= window.y - 50)
    {
        setPosition(getPosition().x, 1);
    }
}
