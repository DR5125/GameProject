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
    // Inicjalizacja tła
    m_FlowSkySprite.setPosition(0.0f, 0.0f);

    // Ustawienie tekstury dla tła
    m_FlowSkyNextSprite.setTexture(m_context->m_assets->GetTexture(BACKGROUND_3));
    m_FlowSkyNext_2Sprite.setTexture(m_context->m_assets->GetTexture(BACKGROUND_3));

    // Inicjalizacja gracza
    player.Init(m_context->m_assets->GetTexture(PLANE));

    // Incjalizacja tekstury paliwa
    fuealTexture = m_context->m_assets->GetTexture(FUEL);
    fuelSprite.setTexture(fuealTexture);
    fuelSprite.setPosition(10,535);
    fuelSprite.setScale(0.2, 0.2);

    // Inicjalizacja tekstury serca
    heartTexture = m_context->m_assets->GetTexture(HEART);
    heartSprite.setTexture(heartTexture);
    heartSprite.setPosition(16,495);
    heartSprite.setScale(0.115, 0.115);

    // punkty

    m_Score.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_Score.setString("Score");
    m_Score.setPosition(630,546);
    m_Score.setCharacterSize(18);
    Score.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    Score.setPosition(715 , 546);
    Score.setCharacterSize(18);

    // Inicjalizacja tabelki punktacji
    scoreBarTx = m_context->m_assets->GetTexture(SCOREBAR);
    scoreBarSp.setTexture(scoreBarTx);
    scoreBarSp.setPosition(599,530);
    scoreBarSp.setScale(1, 0.7);

    // Inicjalizacja paskow zycia
    health = sf::RectangleShape((sf::Vector2f(200.f, 20.f)));
    health.setFillColor(sf::Color::Red);
    health.setPosition(50.f, 505.f);
    underhealth = sf::RectangleShape((sf::Vector2f(206.f, 24.f)));
    underhealth.setFillColor(sf::Color::Black);
    underhealth.setPosition(47.f, 503.f);

    // Inicjalizacja paskow paliwa
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
}

// Przetwarzanie wejścia
void Gameplay::ProcessInput()
{
    // sprawdzanie warunkow przegranej
    if (player.getFuel() <= 0 || player.getLives() <= 0)
    {
        // Przejscie do konca gry
        m_context->m_states->Add(std::make_unique<EndGame>(m_context, player.getScore()));
    }

    // Obsluga klawiszy
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
    // aktualzacja gracza
    player.Animate(deltaTime);
    player.Movement(deltaTime, velocity, m_context->m_window->getSize());


    // Aktualizacja pozycji pierwszego tła
    static const float SKY_SCROLL_SPEED = 20.0f;  // Prędkość przewijania tła
    float offsetX = SKY_SCROLL_SPEED * deltaTime.asSeconds();  // Przesunięcie w osi X

    // Przesuń pierwsze tło w lewo
    sf::Vector2f backgroundPosition = m_FlowSkyNextSprite.getPosition();
    backgroundPosition.x -= offsetX;

    // Sprawdź, czy pierwsza połowa tła przekroczyła środek ekranu
    if (backgroundPosition.x < -m_FlowSkyNextSprite.getGlobalBounds().width / 2)
    {
        // Przesuń pierwsze tło na prawą stronę ekranu, na pozycję (0, 0)
        backgroundPosition.x = 0;
    }

    m_FlowSkyNextSprite.setPosition(backgroundPosition);

    // Aktualizacja pozycji drugiego tła
    sf::Vector2f backgroundPosition2 = m_FlowSkyNext_2Sprite.getPosition();
    backgroundPosition2.x -= offsetX;

    // Sprawdź, czy pierwsza połowa tła przekroczyła środek ekranu
    if (backgroundPosition2.x < -m_FlowSkyNext_2Sprite.getGlobalBounds().width / 2)
    {
        // Przesuń drugie tło na prawą stronę ekranu, na pozycję (0, 0)
        backgroundPosition2.x = 0;
    }

    m_FlowSkyNext_2Sprite.setPosition(backgroundPosition2);


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

    // Aktualizacja punktacji na podstawie czasu gry
    sf::Time elapsedTime = m_gameClock.getElapsedTime();
    int elapsedSeconds = static_cast<int>(elapsedTime.asSeconds());
    m_score = elapsedSeconds;                                       // Przykładowa logika naliczania punktów (jeden punkt na sekundę)
    m_scoreText.setString("Score: " + std::to_string(m_score));     // Aktualizacja tekstu punktacji

    // aktualizacja czasu
    lastspawned += deltaTime;      // zwiekszanie czasu od ostatniego wroga
    lastspawnedbuff += deltaTime;  // zwiekszanie czasu od ostatniego wzmocnienia
    fuelusage += deltaTime;        // zwiekszanie czasu od ostatniego paliwa
    lastshot += deltaTime;         // zwiekszanie czasu od ostatniego strzalu
    progression += deltaTime;      // zwiekszanie czasu od ostatniego zwiekszenia trudnosci

    // zuzycie paliwa
    if (fuelusage.asSeconds() > 1)
    {
        player.setFuel(-2);
        fuelusage = sf::Time::Zero;
    }
    fuel.setScale(player.getFuel()/100.f, 1);
    Score.setString( std::to_string(player.getScore()));  // aktualizacja punktów
    health.setScale(player.getLives() / 100.f, 1);

    // pojawianie sie wzmocnien
    if(lastspawnedbuff.asSeconds()>( 7 + dificulty * 0.3) && quantityBuffs < 3)
    {
        //losowanie typu buffu
        bufftype = rand() % 4;
        quantityBuffs ++;

        if (bufftype == 0 || bufftype == 2)
        {
            //losownanie pozycji
            position = sf::Vector2f(rand() % 700, -20);
            //tworzenie wskaznika na Heal
            buffs.emplace_back(std::make_unique<Heart>(m_context->m_assets->GetTexture(HEART1),position));
        }
        else if (bufftype == 1 || bufftype == 3)
        {
            //losownanie pozycji
            position = sf::Vector2f(rand() % 700, -20);

            //tworzenie wskaznika na Fuel
            buffs.emplace_back(std::make_unique<Fuel>(m_context->m_assets->GetTexture(FUEL1),position));
        }
        lastspawnedbuff = sf::Time::Zero;//zerowanie czasu od ostatniego respu
    }
    // Respienie przeciwników w zale¿noœci od mijajacego czasu
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

    // Poruszanie się dla buffs
    for (auto& object : buffs)
    {
        if (object != nullptr)
        {
            if (auto* heart = dynamic_cast<Heart*>(object.get()))
            {

                heart->Movement(deltaTime, heart->getGlobalBounds(), m_context->m_window->getSize());
            }
            else if (auto* fuel = dynamic_cast<Fuel*>(object.get()))
            {
                fuel->Movement(deltaTime, fuel->getGlobalBounds(), m_context->m_window->getSize());
            }
        }
    }

    // Poruszanie sie dla przeciwników
    for (auto& object : enemies)
    {
        if (object != nullptr)
        {
            // Rzutowanie na odpwoedni typ przeciwnka
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
            }
        }
    }

    // ruch strzalow
    for (auto& object : fireballs)
    {
        if (object != nullptr)
        {
            object->shot(deltaTime);
            object->Animate(deltaTime);
        }
    }

    // Sekcja kolizji
    for (auto& object : enemies)
    {
        if (object != nullptr)
        {
            // kolizja Enemy,player
            if (object->getGlobalBounds().intersects(player.getGlobalBounds()))
            {
                //usuwanie wskaznika i zmiana odpowiednich wartosci w zaleznosci od typu
                if (auto* helicopter = dynamic_cast<Helicopter*>(object.get()))
                {
                    object.reset();
                    player.setLives(-20);
                    player.setScore(-10);

                }
                else if (auto* bat = dynamic_cast<Bat*>(object.get()))
                {
                    object.reset();
                    player.setLives(-5);
                    player.setScore(-5);

                }
            }
            // kolizja Enemy granice ekranu
            if (object != nullptr)
            {
                if (object->getPosition().x + object->getGlobalBounds().width < 0)
                {
                    object.reset();
                }
            }
            // kolizja Enemy,Bullet
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
                                if(helicopter->getLives() == 0)
                                {
                                    expos.emplace_back(std::make_unique<Explosion>(m_context->m_assets->GetTexture(EXPLOSION), helicopter->getPosition()));
                                    object.reset();
                                    shot.reset();
                                    player.setScore(5);
                                }
                                else
                                {
                                    helicopter->setLives();
                                    shot.reset();

                                }

                            }
                            else if (auto* bat = dynamic_cast<Bat*>(object.get()))
                            {
                                expos.emplace_back(std::make_unique<Explosion>(m_context->m_assets->GetTexture(EXPLOSION), bat->getPosition()));
                                object.reset();
                                shot.reset();
                                player.setScore(1);
                            }
                        }
                    }
                }

                // kolizja Bullet z granicami ekranu i usuwanie wskaznika
                if (shot != nullptr)
                {
                    if (shot->getPosition().x > 800)
                    {
                        shot.reset();
                    }
                }
            }
            // animacja expo
            for (auto& object :expos)
            {
                if(object != nullptr)
                {
                    object->Animate(deltaTime);
                    if (object->getLiveTime(deltaTime))
                    {
                        object.reset();
                    }
                }
            }
            // kolizja z wzmocnieniem
            for (auto& object : buffs)
            {
                if (object != nullptr)

                {   // usuwanie wskaznika i zmiana odpowiednich wartoci w zaleznosci od typu
                    if (object->getGlobalBounds().intersects(player.getGlobalBounds()))
                    {
                        if (auto* heart = dynamic_cast<Heart*>(object.get()))
                        {
                            if (player.getLives() < 81)
                            {
                                player.setLives(10);
                            }
                            else if (player.getLives() < 100)
                            {
                                player.setLives(100 - player.getLives());
                            }
                            object.reset();
                            quantityBuffs --;
                        }
                        if (auto* fuel = dynamic_cast<Fuel*>(object.get()))
                        {
                            if (player.getFuel() < 51)
                            {
                                player.setFuel(30);
                            }
                            else if (player.getFuel() < 100)
                            {
                                player.setFuel(100 - player.getFuel());
                            }
                            object.reset();
                            quantityBuffs --;
                        }
                    }
                }
            }
        }
    }
}


// -------------------- Render --------------------
void Gameplay::Draw()
{
    // Clear
    m_context->m_window->clear();

    // Background
    m_context->m_window->draw(m_FlowSkyNextSprite);


    // Clouds
    for (const auto & cloud : clouds)
    {
        m_context->m_window->draw(cloud);
    }
    // Fireballs
    for (auto & object : fireballs)
    {
        if (object != nullptr)
        {
            m_context->m_window->draw(*object);
        }
    }

    // Explosion
    for (auto & object : expos)
    {
        if (object != nullptr)
        {
            m_context->m_window->draw(*object);
        }
    }
    // Enemies
    for (auto & object : enemies)
    {
        if (object != nullptr)
        {
            m_context->m_window->draw(*object);

        }
    }

    // Buffs
    for (auto & object : buffs)
    {
        if (object != nullptr)
        {
            m_context->m_window->draw(*object);
        }
    }

    // Score
    m_context->m_window->draw(scoreBarSp);
    m_context->m_window->draw(m_Score);
    m_context->m_window->draw(Score);

    // Fuel
    m_context->m_window->draw(underfuel);
    m_context->m_window->draw(fuel);
    m_context->m_window->draw(fuelSprite);

    // Hearts
    m_context->m_window->draw(underhealth);
    m_context->m_window->draw(health);
    m_context->m_window->draw(heartSprite);

    // Player
    m_context->m_window->draw(player);

    // Dispaly
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
