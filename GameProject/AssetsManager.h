#ifndef ASSETMAN_H
#define ASSETMAN_H

#include <map>
#include <memory>
#include <string>
#include <iostream>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

/*
 * Klasa "AssetMan" jest odpowiedzialna za zarządzanie zasobami graficznymi gry.
 * Przechowuje tekstury i czcionki w mapach.
 */

namespace Engine
{
    class AssetMan
    {
    public:
        AssetMan();
        ~AssetMan();

        void AddTexture(int id, const std::string &filePath, bool wantRepeated = false);
        // Dodaje teksturę do managera zasobów.
        // Argumenty:
        // - id: unikalny identyfikator tekstury.
        // - filePath: ścieżka do pliku tekstury.
        // - wantRepeated: flaga określająca, czy tekstura ma być powtarzana (domyślnie false).

        void AddFont(int id, const std::string &filePath);
        // Dodaje czcionkę do managera zasobów.
        // Argumenty:
        // - id: unikalny identyfikator czcionki.
        // - filePath: ścieżka do pliku czcionki.

        const sf::Texture &GetTexture(int id) const;
        // Zwraca referencję do tekstury o podanym identyfikatorze.
        // Argument:
        // - id: identyfikator tekstury.
        // Zwracana wartość:
        // - Referencja do tekstury.
        // Uwagi:
        // - Jeśli tekstura o podanym identyfikatorze nie istnieje, może zostać zgłoszony wyjątek lub zwrócona zostanie domyślna tekstura.

        const sf::Font &GetFont(int id) const;
        // Zwraca referencję do czcionki o podanym identyfikatorze.
        // Argument:
        // - id: identyfikator czcionki.
        // Zwracana wartość:
        // - Referencja do czcionki.
        // Uwagi:
        // - Jeśli czcionka o podanym identyfikatorze nie istnieje, może zostać zgłoszony wyjątek lub zwrócona zostanie domyślna czcionka.


    private:
        std::map<int, std::unique_ptr<sf::Texture>> m_textures;
        // Mapa przechowująca tekstury.

        std::map<int, std::unique_ptr<sf::Font>> m_fonts;
        // Mapa przechowująca czcionki.
    };
}

#endif // ASSETMAN_H
