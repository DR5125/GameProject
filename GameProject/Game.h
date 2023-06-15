#ifndef GAME_H
#define GAME_H


#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetsManager.h"
#include "StateManager.h"

/*
 * Klasa "Game" jest odpowiedzialna za zarządzanie główną pętlą gry.
 * Jest to podstawowa klasa, która inicjalizuje zasoby, stany i okno gry, oraz uruchamia pętlę,
 * w której odbywa się aktualizacja i renderowanie gry.
 */


// Ustawienie stałych do rozmieru ekranu
const int HEIGHT = 600;
const int WIDTH = 800;

enum AssetID
{
    MAIN_FONT = 0,
    BACKGROUND = 1,
    BACKGROUND_1 = 10,
    BACKGROUND_2 = 11,
    BACKGROUND_3 = 12,
    MOON_FRAME_1 = 2,
    MOON_FRAME_2 = 3,
    MOON_FRAME_3 = 4,
    MOON_FRAME_4 = 5,
    STARS_FRAME_1 = 6,
    STARS_FRAME_2 = 7,
    STARS_FRAME_3 = 8,
    STARS_FRAME_4 = 9,
    CLOUD_1 = 14,
    CLOUD_2 = 15,
    CLOUD_3 = 16,
    CLOUD_4 = 17,
    CLOUD_5 = 18,
    CLOUD_6 = 19,
    PLANE = 13,
    BAR = 20,
    HELICOPTER = 21,
    BAT = 22,
    FIREBALL = 23,
    EXPLOSION = 24,
    HEART = 25,
    FUEL = 26,
    SCOREBAR = 27,

};
// Enumy zawierająca identyfikatory zasobów.
// Każdy identyfikator reprezentuje inny zasób.

struct Context
{
    std::unique_ptr<Engine::AssetMan> m_assets;
    // Unikalny wskaźnik na obiekt klasy AssetMan, który zarządza zasobami gry.

    std::unique_ptr<Engine::StateMan> m_states;
    // Unikalny wskaźnik na obiekt klasy StateMan, który zarządza stanami gry.

    std::unique_ptr<sf::RenderWindow> m_window;
    // Unikalny wskaźnik na obiekt sf::RenderWindow, który reprezentuje okno gry.

    Context()
    {
        m_assets = std::make_unique<Engine::AssetMan>();
        m_states = std::make_unique<Engine::StateMan>();
        m_window = std::make_unique<sf::RenderWindow>();
    }
    // Konstruktor struktury Context.
    // Tworzy nowe obiekty AssetMan, StateMan i sf::RenderWindow przy użyciu unikalnych wskaźników.
};

class Game
{
public:
    Game();
    ~Game();

    void Run();
    // Metoda uruchamiająca pętlę główną gry.

private:
    std::shared_ptr<Context> m_context;
    // Współdzielony wskaźnik na obiekt klasy Context, który przechowuje kontekst gry (zasoby, stany).

    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
    // Stała określająca czas trwania pojedynczej klatki gry (60 klatek na sekundę).
};

#endif // GAME_H
