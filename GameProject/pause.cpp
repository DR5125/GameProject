#include "Pause.h"

Pause::Pause(std::shared_ptr<Context> &context)
    : m_context(context)
{
}

Pause::~Pause()
{
}

void Pause::Init()
{
    m_Background.setTexture(m_context->m_assets->GetTexture(BACKGROUND_3));

    m_Title.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_Title.setString("PAUSED");
    m_Title.setStyle(sf::Text::Bold);
    m_Title.setCharacterSize(72);
    m_Title.setOrigin(m_Title.getLocalBounds().width / 2, m_Title.getLocalBounds().height / 2);
    m_Title.setPosition(m_context->m_window->getSize().x / 2, 300);
}

void Pause::ProcessInput()
{
    sf::Event ev;
    while (m_context->m_window->pollEvent(ev))
    {
        if (ev.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            m_context->m_states->PopCurrent();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_context->m_window->close();
        }
    }
}

void Pause::Update(const sf::Time& deltaTime) {}

void Pause::Draw()
{
    m_context->m_window->draw(m_Background);
    m_context->m_window->draw(m_Title);
    m_context->m_window->display();
}
