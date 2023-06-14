#ifndef PLAYER_H
#define PLAYER_H


#include <vector>
#include <SFML/Graphics.hpp>

class Player : public sf::Sprite
{
    public:
        Player(); // Konstruktor
        ~Player(); // Destruktor

        void Init(const sf::Texture& texture); // Inicjalizacja gracza
        void Animate(const sf::Time& elapsed); // Animowanie gracza

        void Movement(sf::Time elapsed, sf::Vector2f direction, sf::Vector2u window); // Poruszanie się gracza
        void borders(sf::FloatRect bounds, sf::Vector2u window); // Sprawdzanie granic okna i dostosowywanie pozycji gracza

        void ProcessInput(const sf::Event& event); // Przetwarzanie wejścia


    private:
        float elapsedAccumulator = 0; // Akumulator czasu
        int frame = 0; // Klatka
        const float framePerSecond = 1.0f / 12.0f; // Liczba klatek na sekundę

        sf::Vector2f speed = sf::Vector2f(100.f, 70.f); // Prędkość gracza
        sf::Vector2f gravity = sf::Vector2f(0.f, 10.f); // Wartość grawitacji



};

#endif // PLAYER_H