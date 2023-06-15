#include "Gameplay.h"
#include <SFML/Graphics.hpp>

// Konstruktor
Gameplay::Gameplay(std::shared_ptr<Context>& context) : m_context(context), m_elapsedTime(sf::Time::Zero), m_isPaused(false)
{
    srand(time(nullptr)); // Inicjalizacja generatora liczb pseudolosowych
}

// Destruktor
Gameplay::~Gameplay() {}

// Inicjalizacja
void Gameplay::Init()
{
    //sprawdzanie stanów koñca gry
    if (player.getFuel() <= 0 || player.getLives() <= 0)
    {
        // Dodanie stanu GameOver do stosu stanów gry, przekazanie kontekstu gry i wyniku gracza
        //m_context->m_states->Add(std::make_unique<Gameover>(m_context,player.getScore()), true);
    }

    //inicjalizacja pasków stanów i ich t³a
    health = sf::RectangleShape((sf::Vector2f(200.f, 20.f)));
    health.setFillColor(sf::Color::Red);
    health.setPosition(50.f, 505.f);
    underhealth = sf::RectangleShape((sf::Vector2f(206.f, 24.f)));
    underhealth.setFillColor(sf::Color::Black);
    underhealth.setPosition(47.f, 503.f);
    fuel = sf::RectangleShape((sf::Vector2f(200.f, 20.f)));
    fuel.setFillColor(sf::Color::Yellow);
    fuel.setPosition(50.f, 555.f);
    underfuel = sf::RectangleShape((sf::Vector2f(206.f, 24.f)));
    underfuel.setFillColor(sf::Color::Black);
    underfuel.setPosition(47.f, 553.f);



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

    // Ustawienie tekstury dla tła
    m_FlowSkySprite.setTexture(m_context->m_assets->GetTexture(BACKGROUND_2));

    m_FlowSkyNextSprite.setTexture(m_context->m_assets->GetTexture(BACKGROUND_3));
    m_FlowSkyNext_2Sprite.setTexture(m_context->m_assets->GetTexture(BACKGROUND_3));

    // Inicjalizacja gracza
    player.Init(m_context->m_assets->GetTexture(PLANE));

    // incjalizacja tekstury paliwa
    fuealTexture = m_context->m_assets->GetTexture(FUEL);
    fuelSprite.setTexture(fuealTexture);
    fuelSprite.setPosition(10,535);
    fuelSprite.setScale(0.2, 0.2);

    // inicjalizacja tekstury serca
    heartTexture = m_context->m_assets->GetTexture(HEART);
    heartSprite.setTexture(heartTexture);
    heartSprite.setPosition(16,495);
    heartSprite.setScale(0.115, 0.115);

    // inicjalizacja bara na wynik
    scoreBarTx = m_context->m_assets->GetTexture(SCOREBAR);
    scoreBarSp.setTexture(scoreBarTx);
    scoreBarSp.setPosition(599,530);
    scoreBarSp.setScale(1, 0.7);

    // Inicjalizacja punktacji
    m_score = 0;

    // Ustawienie czcionki dla tekstu punktacji
    m_scoreText.setFont(m_context->m_assets->GetFont(MAIN_FONT));

    m_scoreText.setCharacterSize(18);
    m_scoreText.setPosition(625, 546); // Pozycja tekstu punktacji na ekranie

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

        // Sprawdzenie, czy spacja została naciśnięta i upłynął odpowiedni czas od ostatniego strzału
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && lastshot.asSeconds() > 0.5)
        {
            // Obliczenie pozycji startowej pocisku na podstawie pozycji gracza
            positionplayer.x = player.getPosition().x + player.getGlobalBounds().width / 2;
            positionplayer.y = player.getPosition().y + player.getGlobalBounds().height / 2;

            // Dodanie nowego pocisku do kontenera bullets
            fireballs.emplace_back(std::make_unique<Fireball>(m_context->m_assets->GetTexture(FIREBALL), positionplayer));

            // Zresetowanie czasu ostatniego strzału
            lastshot = sf::Time::Zero;
        }
    }
}

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

    // Enemy
    lastspawned += deltaTime;      // zwiêkszanie czasu od ostatniego pojawienia siê Enemy
    lastspawnedbuff += deltaTime;  // zwiêkszanie czasu od ostatniego pojawienia siê Buffs
    fuelusage += deltaTime;        // zwiêkszanie czasu od ostatniego pobrania paliwa
    lastshot += deltaTime;         // zwiêkszanie czasu od ostatniego strza³u
    progression += deltaTime;      // zwiêkszanie czasu od ostatniego zwiêkszenia trudnoœci

    //zu¿ycie paliwa
    if (fuelusage.asSeconds() > 1)
    {
        player.setFuel(-3);
        fuelusage = sf::Time::Zero;
    }
    health.setScale(player.getLives() / 100.f, 1);
    fuel.setScale(player.getFuel()/100.f, 1);

    // Respienie przeciwników w zale¿noœci od mijaj¹cego czasu
    if (lastspawned.asSeconds() > (3 - dificulty * 0.3))
    {
        // Losowanie typu przeciwnika
        enemytype = rand() % 2;

        if (enemytype == 0)
        {
            // Losowanie pozycji przeciwnika
            position = sf::Vector2f(800.f, rand() % 500);
            // Tworzenie wskaŸnika na Helicopter
            enemies.emplace_back(std::make_unique<Helicopter>(m_context->m_assets->GetTexture(HELICOPTER), position));
        }
        else if (enemytype == 1)
        {
            // Losowanie pozycji przeciwnika
            position = sf::Vector2f(800.f, rand() % 500);
            // Tworzenie wskaŸnika na Baloon
            enemies.emplace_back(std::make_unique<Bat>(m_context->m_assets->GetTexture(BAT), position));
        }

        lastspawned = sf::Time::Zero; // Zerowanie czasu od ostatniego respu
    }

    // Poruszanie sie dla przeciwników
    for (auto& object : enemies)
    {
        if (object != nullptr)
        {
            // Rzutowanie aby okreœliæ typ przeciwnika
            if (auto* helicopter = dynamic_cast<Helicopter*>(object.get()))
            {
                helicopter->Animate(deltaTime);
                helicopter->Movement(deltaTime, helicopter->getGlobalBounds(), m_context->m_window->getSize(), player.getPosition().y);
                helicopter->setRotation(-5);
            }
            else if (auto* bat = dynamic_cast<Bat*>(object.get()))
            {
                bat->Animate(deltaTime);
                bat->Movement(deltaTime, bat->getGlobalBounds(), m_context->m_window->getSize());
                //bat->setRotation(-3);
            }
        }
    }

    // Poruszanie  dla pocisków
    for (auto& object : fireballs)
    {
        if (object != nullptr)
        {
            object->shot(deltaTime);
            object->Animate(deltaTime);
        }
    }

    //kolizja dla przeciwników
    for (auto& object : enemies)
    {
        if (object != nullptr)
        {
            //kolizja Enemy,player
            if (object->getGlobalBounds().intersects(player.getGlobalBounds()))
            {   //usuwanie wskaŸnika i zmiana odpowiednich wartoœci w zale¿noœci od typu
                if (auto* helicopter = dynamic_cast<Helicopter*>(object.get()))
                {
                    object.reset();
                    player.setLives(-20);
                    //player.setScore(-10);
                }
                else if (auto* bat = dynamic_cast<Bat*>(object.get()))
                {
                    object.reset();
                    player.setLives(-5);
                    //player.setScore(-5);
                }
            }
            //kolizja Enemy granice ekranu
            if (object != nullptr)
            {
                if (object->getPosition().x + object->getGlobalBounds().width < 0)
                {
                    object.reset();
                }
            }
            //kolizja Enemy,Bullet
            for (auto& shot : fireballs)
            {
                if (object != nullptr)
                {
                    if (shot != nullptr)
                    {
                        if (object->getGlobalBounds().intersects(shot->getGlobalBounds()))

                        {   //zmiana poziomu zdrowia lub usuwanie wskaŸnika Enemy i Bullet
                            if (auto* helicopter = dynamic_cast<Helicopter*>(object.get()))
                            {
                                if(helicopter->getlives() == 0)
                                {
                                    object.reset();
                                    shot.reset();
                                }
                                else
                                {
                                    helicopter->setlives();
                                    shot.reset();
                                }

                            }
                            else if (auto* bat = dynamic_cast<Bat*>(object.get()))
                            {
                                object.reset();
                                shot.reset();
                            }
                        }
                    }
                }
                //kolizja Bullet z granicami ekranu i usuwanie wskaŸnika
                if (shot != nullptr)
                {
                    if (shot->getPosition().x > 800)
                    {
                        shot.reset();
                    }
                }
            }
        }
    }
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

    //renderowanie Bullet
    for (auto& object : fireballs)
    {
        if (object != nullptr)
        {
            m_context->m_window->draw(*object);
        }
    }

    //renderowanie Enemy
    for (auto& object : enemies)
    {
        if (object != nullptr)
        {
            m_context->m_window->draw(*object);

        }
    }
    m_context->m_window->draw(scoreBarSp);
    m_context->m_window->draw(m_scoreText);
    m_context->m_window->draw(underfuel);
    m_context->m_window->draw(underhealth);
    m_context->m_window->draw(fuel);
    m_context->m_window->draw(health);
    m_context->m_window->draw(fuelSprite);
    m_context->m_window->draw(heartSprite);
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
