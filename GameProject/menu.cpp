#include "Menu.h"

#include "Gameplay.h"

#include "EndGame.h"
#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Context> &context) : m_context(context), m_isPlayButtonSelected(true), m_isPlayButtonPressed(false), m_isExitButtonSelected(false),
      m_isExitButtonPressed(false) {}

MainMenu::~MainMenu() {}

void MainMenu::Init()
{    
    // Wczytanie tekstur Księżyca
    m_context->m_assets->AddTexture(MOON_FRAME_1, "Assets/Textures/Objects/Moon/Frame_1.png");
    m_context->m_assets->AddTexture(MOON_FRAME_2, "Assets/Textures/Objects/Moon/Frame_2.png");
    m_context->m_assets->AddTexture(MOON_FRAME_3, "Assets/Textures/Objects/Moon/Frame_3.png");
    m_context->m_assets->AddTexture(MOON_FRAME_4, "Assets/Textures/Objects/Moon/Frame_4.png");
    // Dodanie kaltek do wektora
    moonFrames.push_back(m_context->m_assets->GetTexture(MOON_FRAME_1));
    moonFrames.push_back(m_context->m_assets->GetTexture(MOON_FRAME_2));
    moonFrames.push_back(m_context->m_assets->GetTexture(MOON_FRAME_3));
    moonFrames.push_back(m_context->m_assets->GetTexture(MOON_FRAME_4));

    // Wczytanie tekstur Gwiazd
    m_context->m_assets->AddTexture(STARS_FRAME_1, "Assets/Textures/Objects/Stars/Frame_1.png");
    m_context->m_assets->AddTexture(STARS_FRAME_2, "Assets/Textures/Objects/Stars/Frame_2.png");
    m_context->m_assets->AddTexture(STARS_FRAME_3, "Assets/Textures/Objects/Stars/Frame_3.png");
    m_context->m_assets->AddTexture(STARS_FRAME_4, "Assets/Textures/Objects/Stars/Frame_4.png");
    // Dodanie kaltek do wektora
    starsFrames.push_back(m_context->m_assets->GetTexture(STARS_FRAME_1));
    starsFrames.push_back(m_context->m_assets->GetTexture(STARS_FRAME_2));
    starsFrames.push_back(m_context->m_assets->GetTexture(STARS_FRAME_3));
    starsFrames.push_back(m_context->m_assets->GetTexture(STARS_FRAME_4));

    // Wczytanie czcionki
    m_context->m_assets->AddFont(MAIN_FONT, "Assets/Fonts/Joystix/joystix.monospace.otf");

    // Inicjalizacja gracza
    m_context->m_assets->AddTexture(PLANE, "Assets/Textures/Objects/Player/PlaneFrames.png");
    // dodanie tekstury helikoptera
    m_context->m_assets->AddTexture(HELICOPTER, "Assets/Textures/Objects/Helicopter/Helicop1.png");

    // dodawanie tekstury
    m_context->m_assets->AddTexture(BAT, "Assets/Textures/Objects/Bat/Bat1.png");

    // dodawanie tekstury pociksu
    m_context->m_assets->AddTexture(FIREBALL, "Assets/Textures/Objects/Fireball/shots.png");

    // dodanie tla do gamplay
    m_context->m_assets->AddTexture(BACKGROUND_2, "Assets/Textures/Backgrounds/PerfectFlow.png");
    m_context->m_assets->AddTexture(BACKGROUND_3, "Assets/Textures/Backgrounds/PerfectFlowNext.png");

    // elementy graficzne heart fuel
    m_context->m_assets->AddTexture(HEART, "Assets/Textures/Objects/Heart/heart1.png");
    m_context->m_assets->AddTexture(FUEL, "Assets/Textures/Objects/Fuel/betterfuel.png");

    // Eksplozja
    m_context->m_assets->AddTexture(EXPLOSION, "Assets/Textures/Objects/Explosion/finalexplo.png");

    // bar na wynik
    m_context->m_assets->AddTexture(SCOREBAR, "Assets/Textures/Objects/Score/bar.png");

    // Tytuł
    m_gameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT)); // Ustawienie czcionki dla tytułu gry
    m_gameTitle.setString("Wind Warrior"); // Ustawienie tekstu dla tytułu gry
    m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2, m_gameTitle.getLocalBounds().height / 2); // Ustawienie punktu centralnego tytułu gry
    float titlePosX = m_context->m_window->getSize().x / 2.f + 50.f; // Obliczenie pozycji X dla tytułu gry
    float titlePosY = m_context->m_window->getSize().y / 2.f - 100.f; // Obliczenie pozycji Y dla tytułu gry
    sf::FloatRect titleBounds = m_gameTitle.getGlobalBounds(); // Pobranie granic tytułu gry
    m_gameTitle.setPosition(titlePosX - titleBounds.width / 2.f, titlePosY - titleBounds.height / 2.f); // Ustawienie pozycji tytułu gry
    m_gameTitle.setCharacterSize(50); // Ustawienie rozmiaru czcionki dla tytułu gry

    // Przycisk "Play"
    m_playButton.setFont(m_context->m_assets->GetFont(MAIN_FONT)); // Ustawienie czcionki dla przycisku "Play"
    m_playButton.setString("Play"); // Ustawienie tekstu dla przycisku "Play"
    m_playButton.setOrigin(m_playButton.getLocalBounds().width / 2, m_playButton.getLocalBounds().height / 2); // Ustawienie punktu centralnego przycisku "Play"
    m_playButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - m_playButton.getLocalBounds().height + 20.f); // Ustawienie pozycji przycisku "Play"
    m_playButton.setCharacterSize(30); // Ustawienie rozmiaru czcionki dla przycisku "Play"

    // Przycisk "Exit"
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT)); // Ustawienie czcionki dla przycisku "Exit"
    m_exitButton.setString("Exit"); // Ustawienie tekstu dla przycisku "Exit"
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2, m_exitButton.getLocalBounds().height / 2); // Ustawienie punktu centralnego przycisku "Exit"
    m_exitButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + m_exitButton.getLocalBounds().height + 30.f); // Ustawienie pozycji przycisku "Exit"
    m_exitButton.setCharacterSize(30); // Ustawienie rozmiaru czcionki dla przycisku "Exit"

    // Wczytaj teksturę tła
    m_context->m_assets->AddTexture(BACKGROUND, "Assets/Textures/Backgrounds/ClearSkyBackground.png");
    m_Sky = m_context->m_assets->GetTexture(BACKGROUND);

    // Ustawienie sprite tła
    m_SkySprite.setTexture(m_Sky);
    m_SkySprite.setPosition(0.f, 0.f);

    // Wczytaj teksture kopii tła
    m_context->m_assets->AddTexture(BACKGROUND_1, "Assets/Textures/Backgrounds/ClearSkyBackground.png");
    m_Sky_2 = m_context->m_assets->GetTexture(BACKGROUND_1);

    // Ustawienie sprite kopii tła
    m_Sky_2Sprite.setTexture(m_Sky_2);
    m_Sky_2Sprite.setPosition(m_SkySprite.getGlobalBounds().width, 0.f);



}

void MainMenu::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed) // Jeśli zdarzenie to zamknięcie okna
        {
            m_context->m_window->close(); // Zamknij okno aplikacji
        }
        else if (event.type == sf::Event::KeyPressed) // Jeśli naciśnięto klawisz
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Up: // Jeśli naciśnięto klawisz strzałki w górę
            {
                if (!m_isPlayButtonSelected) // Jeśli przycisk play nie jest wybrany
                {
                    m_isPlayButtonSelected = true; // Zaznacz przycisk odtwarzania
                    m_isExitButtonSelected = false; // Odznacz przycisk wyjścia
                }
                break;
            }
            case sf::Keyboard::Down: // Jeśli naciśnięto klawisz strzałki w dół
            {
                if (!m_isExitButtonSelected) // Jeśli przycisk wyjścia nie jest wybrany
                {
                    m_isPlayButtonSelected = false; // Odznacz przycisk odtwarzania
                    m_isExitButtonSelected = true; // Zaznacz przycisk wyjścia
                }
                break;
            }
            case sf::Keyboard::Return: // Jeśli naciśnięto klawisz Enter
            {
                m_isPlayButtonPressed = false; // Wyzeruj stan naciśnięcia przycisku odtwarzania
                m_isExitButtonPressed = false; // Wyzeruj stan naciśnięcia przycisku wyjścia

                if (m_isPlayButtonSelected) // Jeśli przycisk odtwarzania jest wybrany
                {
                    m_isPlayButtonPressed = true; // Ustaw stan naciśnięcia przycisku odtwarzania na true
                }
                else // W przeciwnym razie
                {
                    m_isExitButtonPressed = true; // Ustaw stan naciśnięcia przycisku wyjścia na true
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

void MainMenu::Update(const sf::Time& deltaTime)
{
    if (m_isPlayButtonSelected) // Jeśli przycisk odtwarzania jest wybrany
    {
        m_playButton.setFillColor(sf::Color::Black); // Ustaw kolor wypełnienia przycisku odtwarzania na czarny
        m_exitButton.setFillColor(sf::Color::White); // Ustaw kolor wypełnienia przycisku wyjścia na biały
    }
    else // W przeciwnym razie
    {
        m_exitButton.setFillColor(sf::Color::Black); // Ustaw kolor wypełnienia przycisku wyjścia na czarny
        m_playButton.setFillColor(sf::Color::White); // Ustaw kolor wypełnienia przycisku odtwarzania na biały
    }

    if (m_isPlayButtonPressed)
    {
        // Aktywuj nowy stan gry "Gameplay"
        m_context->m_states->Add(std::make_unique<Gameplay>(m_context), true);
    }
    else if (m_isExitButtonPressed)
    {
        // Zamknij okno aplikacji
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

void MainMenu::Draw()
{
    m_context->m_window->clear(sf::Color::Black);
    m_context->m_window->draw(m_SkySprite);
    m_context->m_window->draw(m_MoonSprite);
    m_context->m_window->draw(m_StarsSprite);
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->draw(m_playButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}
