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
    EndGame(std::shared_ptr<Context> &context);
    ~EndGame();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;

private:
    std::shared_ptr<Context> m_context;
    sf::Text m_gameOverTitle;
    sf::Text m_retryButton;
    sf::Text m_exitButton;

    sf::Texture m_Sky;
    sf::Sprite m_SkySprite;
    sf::Texture m_Sky_2;
    sf::Sprite m_Sky_2Sprite;
    sf::Sprite m_MoonSprite;
    sf::Sprite m_StarsSprite;
    std::vector<sf::Texture> moonFrames;
    std::vector<sf::Texture> starsFrames;

    bool m_isRetryButtonSelected;
    bool m_isRetryButtonPressed;

    bool m_isExitButtonSelected;
    bool m_isExitButtonPressed;
};

#endif // ENDGAME_H
