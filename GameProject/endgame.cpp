#include "EndGame.h"
#include "Gameplay.h"

#include <SFML/Window/Event.hpp>

EndGame::EndGame(std::shared_ptr<Context> &context)
    : m_context(context), m_isRetryButtonSelected(true),
      m_isRetryButtonPressed(false), m_isExitButtonSelected(false),
      m_isExitButtonPressed(false)
{
}

EndGame::~EndGame()
{
}

void EndGame::Init()
{

    m_gameOverTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT)); // Ustawienie czcionki dla tytułu gry
    m_gameOverTitle.setString("Game Over"); // Ustawienie tekstu dla tytułu gry
    m_gameOverTitle.setOrigin(m_gameOverTitle.getLocalBounds().width / 2, m_gameOverTitle.getLocalBounds().height / 2); // Ustawienie punktu centralnego tytułu gry
    float titlePosX = m_context->m_window->getSize().x / 2.f + 50.f; // Obliczenie pozycji X dla tytułu gry
    float titlePosY = m_context->m_window->getSize().y / 2.f - 100.f; // Obliczenie pozycji Y dla tytułu gry
    sf::FloatRect titleBounds = m_gameOverTitle.getGlobalBounds(); // Pobranie granic tytułu gry
    m_gameOverTitle.setPosition(titlePosX - titleBounds.width / 2.f, titlePosY - titleBounds.height / 2.f); // Ustawienie pozycji tytułu gry
    m_gameOverTitle.setCharacterSize(50); // Ustawienie rozmiaru czcionki dla tytułu gry


    // Przycisk "Play"
    m_retryButton.setFont(m_context->m_assets->GetFont(MAIN_FONT)); // Ustawienie czcionki dla przycisku "Play"
    m_retryButton.setString("Try Again"); // Ustawienie tekstu dla przycisku "Play"
    m_retryButton.setOrigin(m_retryButton.getLocalBounds().width / 2, m_retryButton.getLocalBounds().height / 2); // Ustawienie punktu centralnego przycisku "Play"
    m_retryButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - m_retryButton.getLocalBounds().height + 20.f); // Ustawienie pozycji przycisku "Play"
    m_retryButton.setCharacterSize(30); // Ustawienie rozmiaru czcionki dla przycisku "Play"

    // Przycisk "Exit"
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT)); // Ustawienie czcionki dla przycisku "Exit"
    m_exitButton.setString("Exit"); // Ustawienie tekstu dla przycisku "Exit"
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2, m_exitButton.getLocalBounds().height / 2); // Ustawienie punktu centralnego przycisku "Exit"
    m_exitButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + m_exitButton.getLocalBounds().height + 30.f); // Ustawienie pozycji przycisku "Exit"
    m_exitButton.setCharacterSize(30); // Ustawienie rozmiaru czcionki dla przycisku "Exit"

    // Wczytaj teksturę tła
    m_Sky = m_context->m_assets->GetTexture(BACKGROUND_3);

    // Ustawienie sprite tła
    m_SkySprite.setTexture(m_Sky);
    m_SkySprite.setPosition(0.f, 0.f);

    // Wczytaj teksture kopii tła
    m_Sky_2 = m_context->m_assets->GetTexture(BACKGROUND_3);

    // Ustawienie sprite kopii tła
    m_Sky_2Sprite.setTexture(m_Sky_2);
    m_Sky_2Sprite.setPosition(m_SkySprite.getGlobalBounds().width, 0.f);
}

void EndGame::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
            {
                if (!m_isRetryButtonSelected)
                {
                    m_isRetryButtonSelected = true;
                    m_isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                if (!m_isExitButtonSelected)
                {
                    m_isRetryButtonSelected = false;
                    m_isExitButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                m_isRetryButtonPressed = false;
                m_isExitButtonPressed = false;

                if (m_isRetryButtonSelected)
                {
                    m_isRetryButtonPressed = true;
                }
                else
                {
                    m_isExitButtonPressed = true;
                }

                break;
            }
            default:
            {
                break;
            }
            }
        }
    }
}

void EndGame::Update(const sf::Time& deltaTime)
{
    if (m_isRetryButtonSelected)
    {
        m_retryButton.setFillColor(sf::Color::Black);
        m_exitButton.setFillColor(sf::Color::White);
    }
    else
    {
        m_exitButton.setFillColor(sf::Color::Black);
        m_retryButton.setFillColor(sf::Color::White);
    }

    if (m_isRetryButtonPressed)
    {
        // Aktywuj nowy stan gry "Gameplay"
        m_context->m_states->Add(std::make_unique<Gameplay>(m_context), true);
    }
    else if (m_isExitButtonPressed)
    {
        m_context->m_window->close();
    }
    // Animacja Księżyca
    static const float MOON_FRAME_DURATION = 0.4f;    // Czas trwania jednej klatki Księżyca (w sekundach)
    static float moonFrameTimer = 0.0f;               // Licznik czasu dla Księżyca
    static unsigned int currentMoonFrame = 0;         // Bieżąca klatka Księżyca

    // Animacja Stars
    static const float STARS_FRAME_DURATION = 0.3f;   // Czas trwania jednej klatki Stars (w sekundach)
    static float starsFrameTimer = 0.0f;              // Licznik czasu dla Stars
    static unsigned int currentStarsFrame = 0;        // Bieżąca klatka Stars

    moonFrameTimer += deltaTime.asSeconds(); // Zwiększaj licznik czasu dla klatek księżyca na podstawie czasu od ostatniej aktualizacji
    starsFrameTimer += deltaTime.asSeconds(); // Zwiększaj licznik czasu dla klatek gwiazd na podstawie czasu od ostatniej aktualizacji

    if (moonFrameTimer >= MOON_FRAME_DURATION) // Jeśli licznik czasu dla klatek księżyca przekroczy ustaloną wartość
    {
        moonFrameTimer = 0.0f; // Zresetuj licznik czasu
        currentMoonFrame = (currentMoonFrame + 1) % moonFrames.size(); // Przełącz na następną klatkę księżyca, uwzględniając warunek cyklicznego indeksowania
        m_MoonSprite.setTexture(moonFrames[currentMoonFrame]); // Ustaw nową teksturę dla sprite'a księżyca
    }

    if (starsFrameTimer >= STARS_FRAME_DURATION) // Jeśli licznik czasu dla klatek gwiazd przekroczy ustaloną wartość
    {
        starsFrameTimer = 0.0f; // Zresetuj licznik czasu
        currentStarsFrame = (currentStarsFrame + 1) % starsFrames.size(); // Przełącz na następną klatkę gwiazd, uwzględniając warunek cyklicznego indeksowania
        m_StarsSprite.setTexture(starsFrames[currentStarsFrame]); // Ustaw nową teksturę dla sprite'a gwiazd
    }

    // Aktualizacja pozycji pierwszego tła
    static const float SKY_SCROLL_SPEED = 20.0f;  // Prędkość przewijania tła
    float offsetX = SKY_SCROLL_SPEED * deltaTime.asSeconds();  // Przesunięcie w osi X

    // Przesuń pierwsze tło w lewo
    sf::Vector2f backgroundPosition = m_SkySprite.getPosition();
    backgroundPosition.x -= offsetX;

    // Sprawdź, czy pierwsza połowa tła przekroczyła środek ekranu
    if (backgroundPosition.x < -m_SkySprite.getGlobalBounds().width / 2)
    {
        // Przesuń pierwsze tło na prawą stronę ekranu, na pozycję (0, 0)
        backgroundPosition.x = 0;
    }

    m_SkySprite.setPosition(backgroundPosition);

    // Aktualizacja pozycji drugiego tła
    sf::Vector2f backgroundPosition2 = m_Sky_2Sprite.getPosition();
    backgroundPosition2.x -= offsetX;

    // Sprawdź, czy pierwsza połowa tła przekroczyła środek ekranu
    if (backgroundPosition2.x < -m_Sky_2Sprite.getGlobalBounds().width / 2)
    {
        // Przesuń drugie tło na prawą stronę ekranu, na pozycję (0, 0)
        backgroundPosition2.x = 0;
    }

    m_Sky_2Sprite.setPosition(backgroundPosition2);
}

void EndGame::Draw()
{
    m_context->m_window->clear(sf::Color::Black);
    m_context->m_window->draw(m_SkySprite);
    m_context->m_window->draw(m_MoonSprite);
    m_context->m_window->draw(m_StarsSprite);
    m_context->m_window->draw(m_gameOverTitle);
    m_context->m_window->draw(m_retryButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}
