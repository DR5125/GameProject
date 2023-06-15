#ifndef ENDGAME_H
#define ENDGAME_H

#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "Game.h"

class EndGame : public Engine::State
{
public:
    EndGame(std::shared_ptr<Context> &context, int score);
    ~EndGame();

    void Init() override;                            // Inicjalizacja stanu
    void ProcessInput() override;                    // Obsługa wejścia
    void Update(const sf::Time& deltaTime) override; // Aktualizacja logiki stanu
    void Draw() override;                            // Rysowanie stanu

private:
    std::shared_ptr<Context> m_context;              // Wskaźnik na kontekst gry

    sf::Text scoring; // Tekst z wynikiem
    int points; // Liczba zdobytych punktów

    // Teksty używane w ekranie zakończenia gry
    sf::Text m_gameOverTitle;
    sf::Text m_retryButton;
    sf::Text m_exitButton;

    // Grafiki używane w tle ekranu zakończenia gry
    sf::Texture m_Sky;
    sf::Sprite m_SkySprite;
    sf::Texture m_Sky_2;
    sf::Sprite m_Sky_2Sprite;

    // Flagi informujące o stanie przycisków
    bool m_isRetryButtonSelected;
    bool m_isRetryButtonPressed;

    bool m_isExitButtonSelected;
    bool m_isExitButtonPressed;
};

#endif // ENDGAME_H
