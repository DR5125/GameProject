#include "AssetsManager.h"

Engine::AssetMan::AssetMan()
{
}

Engine::AssetMan::~AssetMan()
{
}

void Engine::AssetMan::AddTexture(int id, const std::string &filePath, bool wantRepeated)
{
    auto texture = std::make_unique<sf::Texture>(); // Tworzenie unikalnego wskaźnika do tekstury

    if (texture->loadFromFile(filePath)) // Ładowanie tekstury z pliku
    {
        texture->setRepeated(wantRepeated); // Ustawianie powtarzalności tekstury
        m_textures[id] = std::move(texture); // Dodawanie tekstury do mapy tekstur
    }
    else
    {
        std::cerr << "Failed to load " << filePath << std::endl;
    }
}

void Engine::AssetMan::AddFont(int id, const std::string &filePath)
{
    auto font = std::make_unique<sf::Font>(); // Tworzenie unikalnego wskaźnika do czcionki

    if (font->loadFromFile(filePath)) // Ładowanie czcionki z pliku
    {
        m_fonts[id] = std::move(font); // Dodawanie czcionki do mapy czcionek
    }
    else
    {
        std::cerr << "Failed to load " << filePath << std::endl;
    }
}

const sf::Texture &Engine::AssetMan::GetTexture(int id) const
{
    return *(m_textures.at(id).get()); // Pobieranie tekstury o określonym identyfikatorze
}

const sf::Font &Engine::AssetMan::GetFont(int id) const
{
    return *(m_fonts.at(id).get()); // Pobieranie czcionki o określonym identyfikatorze
}
