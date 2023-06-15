#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "EndGame.h"
#include "Bat.h"
#include "Heart.h"
#include "Fuel.h"
#include "Helicopter.h"
#include "Fireball.h"
#include "Explosion.h"
#include "Player.h"
#include "Game.h"
#include "State.h"
#include "Pause.h"

#include <memory>
#include <array>
#include <vector>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class Gameplay : public Engine::State
{
    public:
        Gameplay(std::shared_ptr<Context>& context);        // Konstruktor
        ~Gameplay();                                        // Destruktor

        void Init() override;                               // Inicjalizacja
        void ProcessInput() override;                       // Przetwarzanie wejscia
        void Update(const sf::Time& deltaTime) override;    // Aktualizacja
        void Draw() override;                               // Renderowanie
        void Pause() override;                              // Pauza
        void Start() override;                              // Start

    private:
        std::shared_ptr<Context> m_context;                 // Wskaźnik na kontekst

        // Sekcja czasu -----------------------------------------------------------------------
        sf::Time m_elapsedTime;                             // uplywajacy czas
        sf::Clock m_gameClock;                              // zegar mierzący czas gry
        sf::Time lastspawned;                               // czas od ostatniego pojawienia się przeciwnika
        sf::Time lastspawnedbuff;                           // czas od ostatniego pojawienia się buffa
        sf::Time lastshot=sf::Time::Zero;                   // czas od ostatniego wystrzału
        sf::Time fuelusage=sf::Time::Zero;                  // czas od ostatniego zużycia paliwa
        sf::Time progression=sf::Time::Zero;                // czas od ostatniego podniesienia trudności

        // Sekcja chmur -----------------------------------------------------------------------
        static const int max_clouds = 8;                    // maksymalna liczba chmur
        sf::Time cloudSpawnTimer;                           // deklaracja zmiennej cloudSpawnTimer
        std::vector<sf::Sprite> clouds;                     // wektor sprite dla chmur
        float cloudsVelocity = -80;                         // predkosc chmur
        float SKY_SCROLL_SPEED_X = 20.0f;                   // prędkość przewijania tła w osi X
        float SKY_SCROLL_SPEED_Y = 30.0f;                   // prędkość przewijania tła w osi Y

        // Skecja gracza ----------------------------------------------------------------------
        sf::Vector2f velocity;                              // prędkość poruszania się gracza
        Player player;                                      // obiekt gracza
        sf::Vector2f positionplayer;                        // pozycja gracza

        // Sekcja tla -------------------------------------------------------------------------
        sf::Sprite m_FlowSkySprite;                         // sprite pierwszego tła
        sf::Sprite m_FlowSkyNextSprite;                     // sprite drugiego tła
        sf::Sprite m_FlowSkyNext_2Sprite;                   // sprite trzeciego tła

        // Sekcja punktacji -------------------------------------------------------------------

        sf::Text m_Score; // Tekst z napiesem wynik
        sf::Text Score; // Tekst z wynikiem

        int m_score;                                        // aktualna punktacja
        sf::Text m_scoreText;                               // tekst wyświetlający punktację
        sf::Font m_font;                                    // czcionka dla tekstu punktacji
        sf::Sprite scoreBarSp;                              // sprite dla tabliczki od punktacji
        sf::Texture scoreBarTx;                             // tekstura dla tabliczki od punktacji

        // Sekcja wroga -----------------------------------------------------------------------
        int enemytype;                                      // zmienna do losowania typu przeciwnika
        std::vector<std::unique_ptr<Enemy>> enemies;        // wektor unikalnych wskaźników enemy

        // Sekcja wzmocnien -------------------------------------------------------------------
        int bufftype;                                       // zmienna do losowania typu buffa
        std::vector<std::unique_ptr<Reinforcements>> buffs; // wektor unikalnych wskaźników reinforcements

        // Sekcja zdrowia ---------------------------------------------------------------------
        sf::Sprite heartSprite;                             // sprite dla serca
        sf::Texture heartTexture;                           // tekstura dla serca
        sf::RectangleShape health;                          // pasek zdrowia
        sf::RectangleShape underhealth;                     // tło paska zdrownia

        // Sekcja paliwa ----------------------------------------------------------------------
        sf::Sprite fuelSprite;                              // sprite dla paliwa
        sf::Texture fuealTexture;                           // tekstura dla paliwa
        sf::RectangleShape fuel;                            // pasek paliwa
        sf::RectangleShape underfuel;                       // tło paska paliwa

        // Sekcja pociskow --------------------------------------------------------------------
        std::vector<std::unique_ptr<Fireball>> fireballs;   // Wektor unikalnych wskaźników na obiekty typu Bullet

        // Inne -------------------------------------------------------------------------------
        int dificulty = 2;                                  // wspołczynnik trudnosci
        sf::Vector2f position;                              // pozycja
        int random_number;                                  // zmeinna do wartosci losowej
        bool m_isPaused;                                    // bool do pauzy
        sf::Event event;                                    // zmienna do obslugi zdarzen
        std::vector<std::unique_ptr<Explosion>> expos;

        int quantityBuffs = 0;
};

#endif // GAMEPLAY_H
