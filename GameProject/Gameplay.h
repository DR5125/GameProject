#ifndef GAMEPLAY_H
#define GAMEPLAY_H


#include <memory>
#include <array>
#include <vector>
#include "Bat.h"
#include "Helicopter.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Player.h"
#include "Game.h"
#include "State.h"


class Gameplay : public Engine::State
{
    public:
        Gameplay(std::shared_ptr<Context>& context); // Konstruktor
        ~Gameplay(); // Destruktor

        void Init() override; // Inicjalizacja
        void ProcessInput() override; // Przetwarzanie wejścia
        void Update(const sf::Time& deltaTime) override; // Aktualizacja
        void Draw() override; // Renderowanie
        void Pause() override; // Pauza
        void Start() override; // Start

    private:
        std::shared_ptr<Context> m_context; // Wskaźnik na kontekst aplikacji
        sf::Time m_elapsedTime; // Upływający czas
        bool m_isPaused; // Flaga wskazująca, czy gra jest w trybie pauzy

        static const int max_clouds = 10; // Maksymalna liczba chmur
        sf::Time cloudSpawnTimer; // Deklaracja zmiennej cloudSpawnTimer

        sf::Vector2f velocity; // Prędkość poruszania się gracza
        Player player; // Obiekt gracza

        sf::Sprite m_FlowSkySprite; // Sprite pierwszego tła
        sf::Sprite m_FlowSkyNextSprite; // Sprite drugiego tła
        sf::Sprite m_FlowSkyNext_2Sprite; // Sprite trzeciego tła

        std::vector<sf::Sprite> clouds; // wektor sprite dla chmur
        float cloudsVelocity = -80;

        int m_score;                  // Aktualna punktacja
        sf::Clock m_gameClock;        // Zegar mierzący czas gry
        sf::Text m_scoreText;         // Tekst wyświetlający punktację
        sf::Font m_font;              // Czcionka dla tekstu punktacji

        // enenmy
        int random_number;
        int enemytype;//zmienna do losowania typu przeciwnika
        sf::Time lastspawned;// Czas od ostatniego pojawienia się przeciwnika
        sf::Time lastspawnedbuff;// Czas od ostatniego pojawienia się buffa
        sf::Time lastshot=sf::Time::Zero;// Czas od ostatniego wystrzału
        sf::Time fuelusage=sf::Time::Zero;// Czas od ostatniego zużycia paliwa
        sf::Time progression=sf::Time::Zero;// Czas od ostatniego podniesienia trudności
        int dificulty = 1;//współczynnik trudności
        std::vector<std::unique_ptr<Enemy>> enemies;// Wektor unikalnych wskaźników na obiekty typu Enemy
        sf::Vector2f position;
        sf::Vector2f positionplayer;//pozycja gracza

};

#endif // GAMEPLAY_H
