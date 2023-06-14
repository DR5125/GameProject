#include "Gameplay.h"
#include <SFML/Graphics.hpp>

// Konstruktor
Gameplay::Gameplay(std::shared_ptr<Context>& context) : m_context(context), m_elapsedTime(sf::Time::Zero), m_isPaused(false)
{
    srand(time(nullptr));
}

// Destruktor
Gameplay::~Gameplay() {}

// Inicjalizacja
void Gameplay::Init()
{
    // Inicjalizacja punktacji
    m_score = 0;
    m_scoreText.setFont(m_context->m_assets->GetFont(MAIN_FONT)); // Ustawienie czcionki
    m_scoreText.setCharacterSize(25);
    m_scoreText.setPosition(600, 535);  // Pozycja tekstu punktacji na ekranie

    // Wczytanie tekstur chmur
    for (int i = 1; i <= 6; ++i)
    {
        std::string texturePath = "Assets/Textures/Objects/Clouds/Cloud-" + std::to_string(i) + ".png";
        m_context->m_assets->AddTexture(AssetID(i), texturePath);
    }

    // Dodawanie chmur do wektora
    for (int i = 0; i < max_clouds; ++i)
    {
        sf::Sprite cloud;
        float random_number = 1 + rand() % 6;
        AssetID randomCloud = static_cast<AssetID>(random_number);
        cloud.setTexture(m_context->m_assets->GetTexture(randomCloud));

        // Losowanie pozycji x i y dla chmury
        float randomX = 800 + rand() % 1300;
        float randomY = 0 + rand() % 500;
        cloud.setPosition(sf::Vector2f(randomX, randomY));

        clouds.push_back(cloud);
    }



    // Inicjalizacja tła
    m_FlowSkySprite.setPosition(0.0f, 0.0f);
    m_context->m_assets->AddTexture(BACKGROUND_2, "Assets/Textures/Backgrounds/PerfectFlow.png");
    m_FlowSkySprite.setTexture(m_context->m_assets->GetTexture(BACKGROUND_2));
    m_context->m_assets->AddTexture(BACKGROUND_3, "Assets/Textures/Backgrounds/PerfectFlowNext.png");
    m_FlowSkyNextSprite.setTexture(m_context->m_assets->GetTexture(BACKGROUND_3));
    m_FlowSkyNext_2Sprite.setTexture(m_context->m_assets->GetTexture(BACKGROUND_3));

    // Inicjalizacja gracza
    m_context->m_assets->AddTexture(PLANE, "Assets/Textures/Objects/Player/PlaneFrames.png");
    player.Init(m_context->m_assets->GetTexture(PLANE));
}

// Przetwarzanie wejścia
void Gameplay::ProcessInput()
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
            if (event.key.code == sf::Keyboard::Up)
            {
                velocity.y = -1.0f;
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                velocity.y = 1.0f;
            }
            else if (event.key.code == sf::Keyboard::Left)
            {
                velocity.x = -1.0f;
            }
            else if (event.key.code == sf::Keyboard::Right)
            {
                velocity.x = 1.0f;
            }
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
            {
                velocity.y = 0.0f;
            }
            else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
            {
                velocity.x = 0.0f;
            }
        }
    }
}

// Aktualizacja
void Gameplay::Update(const sf::Time& deltaTime)
{
    static const float SKY_SCROLL_SPEED_X = 20.0f; // Prędkość przewijania tła w osi X
    static const float SKY_SCROLL_SPEED_Y = 30.0f; // Prędkość przewijania tła w osi Y
    float offsetX = SKY_SCROLL_SPEED_X * deltaTime.asSeconds(); // Przesunięcie w osi X
    float offsetY = SKY_SCROLL_SPEED_Y * deltaTime.asSeconds(); // Przesunięcie w osi Y

    // Aktualizacja pozycji tła
    m_FlowSkySprite.move(-offsetX, -offsetY);

    // Sprawdzenie, czy tło przekroczyło ekran
    if (m_FlowSkySprite.getPosition().x + m_FlowSkySprite.getGlobalBounds().width <= 0.0f)
    {
        m_FlowSkySprite.setPosition(0.0f, 0.0f);
    }

    // Aktualizacja pozycji chmur
    for (auto& cloud : clouds)
    {
        cloud.move(cloudsVelocity * deltaTime.asSeconds(), 0.0f);

        // Sprawdzenie, czy chmura przekroczyła ekran
        if (cloud.getPosition().x + cloud.getGlobalBounds().width <= 0.0f)
        {
            // Losowanie nowej tekstury chmury
            float random_number = 1 + rand() % 6;
            AssetID randomCloud = static_cast<AssetID>(random_number);
            cloud.setTexture(m_context->m_assets->GetTexture(randomCloud));

            // Ustawienie losowej pozycji y
            float randomY = 0 + rand() % m_context->m_window->getSize().y;
            cloud.setPosition(sf::Vector2f(m_context->m_window->getSize().x, randomY));
        }
    }

    player.Animate(deltaTime);
    player.Movement(deltaTime, velocity, m_context->m_window->getSize());

    // Aktualizacja punktacji na podstawie czasu gry
    sf::Time elapsedTime = m_gameClock.getElapsedTime();
    int elapsedSeconds = static_cast<int>(elapsedTime.asSeconds());
    m_score = elapsedSeconds;  // Przykładowa logika naliczania punktów (jeden punkt na sekundę)

    // Aktualizacja tekstu punktacji
    m_scoreText.setString("Score: " + std::to_string(m_score));


    // tu jest meijsce na ENDGAME
    /*
     * m_context->m_states->Add(std::make_unique<EndGame>(m_context));
     * break;
     */
}


// Renderowanie
void Gameplay::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_FlowSkySprite);

    // Wyświetlanie chmur
    for (const auto& cloud : clouds)
    {
        m_context->m_window->draw(cloud);
    }

    m_context->m_window->draw(m_scoreText);
    m_context->m_window->draw(player);
    m_context->m_window->display();
}

// Pauza
void Gameplay::Pause()
{
    m_isPaused = true;
}

// Start
void Gameplay::Start()
{
    m_isPaused = false;
}
