#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SFML/Graphics.hpp>

class Explosion : public sf::Sprite
{
public:
    Explosion(const sf::Texture& texture, const sf::Vector2f& playerPosition);
    ~Explosion();

    void Animate(sf::Time DeltaTime);               // Metoda animacji
    bool getLiveTime(sf::Time DeltaTime);
private:
    sf::Texture texture;
    sf::Vector2f speed = sf::Vector2f(100.f, 70.f);
    int frame = 0;                                  // Numer aktualnej klatki animacji
    float frameTime = 1.0f / 10;                    // Czas trwania jednej klatki animacji
    float accumulatedtime = 0;                      // Całkowity czas dla animacji
    sf::Time liveTime;

};

#endif // EXPLOSION_H
