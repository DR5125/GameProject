#ifndef PAUSE_H
#define PAUSE_H

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "Game.h"

class Pause : public Engine::State
{
public:
    Pause(std::shared_ptr<Context> &context);
    ~Pause();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;

private:
    std::shared_ptr<Context> m_context;
    sf::Text m_pauseTitle;
};

#endif // PAUSE_H
