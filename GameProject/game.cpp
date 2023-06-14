#include "Game.h"

#include <SFML/Graphics/CircleShape.hpp>

#include "Menu.h"



Game::Game() : m_context(std::make_shared<Context>())
{
    m_context->m_window->create(sf::VideoMode(WIDTH, HEIGHT), "Wind Warrior");//, sf::Style::Close);
    m_context->m_states->Add(std::make_unique<MainMenu>(m_context));
}

Game::~Game()
{
}

void Game::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (m_context->m_window->isOpen()) // Pętla główna gry
    {
        timeSinceLastFrame += clock.restart(); // Zwiększ czas od ostatniej klatki gry

        while (timeSinceLastFrame > TIME_PER_FRAME) // Dopóki czas od ostatniej klatki jest większy od ustalonego czasu na jedną klatkę
        {
            timeSinceLastFrame -= TIME_PER_FRAME; // Pomniejsz czas od ostatniej klatki o ustalony czas na jedną klatkę

            m_context->m_states->ProcessStateChange(); // Przetwórz zmiany stanu
            m_context->m_states->GetCurrent()->ProcessInput(); // Przetwórz dane wejściowe dla aktualnego stanu
            m_context->m_states->GetCurrent()->Update(TIME_PER_FRAME); // Zaktualizuj logikę dla aktualnego stanu
            m_context->m_states->GetCurrent()->Draw(); // Narysuj aktualny stan
        }
    }
}
