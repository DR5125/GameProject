#ifndef HELICOPTER_H
#define HELICOPTER_H

#include"Enemy.h"
class Helicopter:public Enemy
{
private:
    sf::Texture texture;
    int frame = 0; // Numer bie¿¹cej klatki animacji
    float frameTime = 1.0f / 10; // Czas trwania jednej klatki animacji
    float accumulatedtime = 0; // ca³owity czas dla animacji
    sf::Vector2f speed = sf::Vector2f(-100.f, 35.f);
    int lives = 2;

public:
    //konstruktor destruktor
    Helicopter(const sf::Texture& texture,sf::Vector2f position);
    ~Helicopter();

     void Animate(sf::Time DeltaTime);// Animacja helikoptera
     void Movement(sf::Time DeltaTime, sf::FloatRect bounds, sf::Vector2u window,float directiony);// Ruch helikoptera w kierunku gracza
     void setlives();//zmienianie ¿ycia
     int getlives();//pobieranie ¿ycia
};

#endif // HELICOPTER_H
