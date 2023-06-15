#ifndef MAINMENU_H
#define MAINMENU_H

#include <memory>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>

#include "State.h"
#include "Game.h"

/*
 * Klasa "MainMenu" jest reprezentacją stanu gry, który odpowiada za wyświetlanie głównego menu gry.
 * Umożliwia interakcję poprzez przyciski.
 * Klasa ta dziedziczy po klasie "Engine::State",
 * co oznacza, że implementuje wymagane metody stanu gry, takie jak Init(), ProcessInput(), Update() i Draw().
 */

class MainMenu : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    // Współdzielony wskaźnik na obiekt klasy Context, który przechowuje kontekst gry (zasoby, stany, okno).

    sf::Text m_gameTitle;
    sf::Text m_playButton;
    sf::Text m_exitButton;

    sf::Texture m_Sky;
    sf::Sprite m_SkySprite;
    sf::Texture m_Sky_2;
    sf::Sprite m_Sky_2Sprite;
    sf::Sprite m_MoonSprite;
    sf::Sprite m_StarsSprite;
    std::vector<sf::Texture> moonFrames;
    std::vector<sf::Texture> starsFrames;
    sf::Event event;
    // Flagi oznaczające czy dany przycisk jest wybrany lub naciśnięty
    bool m_isPlayButtonSelected;
    bool m_isPlayButtonPressed;

    bool m_isExitButtonSelected;
    bool m_isExitButtonPressed;

public:
    MainMenu(std::shared_ptr<Context> &context);
    ~MainMenu();

    void Init() override;
    // Metoda inicjalizująca stan MainMenu.
    // Tworzy i konfiguruje elementy interfejsu, ustawia tekstury, itp.

    void ProcessInput() override;
    // Metoda obsługująca zdarzenia wejściowe (np. klawiatury, myszy) w MainMenu.
    // Reaguje na interakcje użytkownika (np. najechanie myszą na przyciski, kliknięcie).

    void Update(const sf::Time& deltaTime) override;
    // Metoda aktualizująca logikę MainMenu.
    // Wykonuje odpowiednie operacje, które powinny być wykonane w każdej klatce gry.

    void Draw() override;
    // Metoda renderująca elementy MainMenu na ekranie.
    // Wyświetla tytuł, przyciski, tło, animacje itp.
};

#endif // MAINMENU_H
