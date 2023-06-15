#ifndef PAUSE_H
#define PAUSE_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "State.h"
#include "game.h"

class Pause : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    sf::Text m_Title;
    sf::Sprite m_Background;

public:
    Pause(std::shared_ptr<Context> &context);
    ~Pause();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
};

#endif // PAUSE_H
