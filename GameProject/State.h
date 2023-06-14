#ifndef STATE_H
#define STATE_H

#include <SFML/System/Time.hpp>

/*
 *  Klasa "State" reprezentuje abstrakcyjny stan w silniku gry.
 *  Jest podstawową do tworzenia różnych stanów w grze.
 *  Funkcjonalność tej klasy polega na zapewnieniu interfejsu,
 *  który musi być zaimplementowany przez wszystkie konkretne stany w grze.
 *
 *  Użycie namespace Engine pozwala na lepszą organizację kodu,
 *  ponieważ wszystkie elementy związane z silnikiem gry są zgrupowane razem.
 */


namespace Engine
{
    class State
    {
    public:
        State(){};
        virtual ~State(){};

        // Metoda czysto wirtualna odpowiedzialna za inicjalizację stanu.
        virtual void Init() = 0;


        virtual void ProcessInput() = 0;
        // Metoda czysto wirtualna odpowiedzialna za przetwarzanie danych wejściowych.

        virtual void Update(const sf::Time& deltaTime) = 0;
        // Metoda czysto wirtualna odpowiedzialna za aktualizację stanu na podstawie upływającego czasu.
        // Argument 'deltaTime': czas od ostatniego wywołania metody Update().

        virtual void Draw() = 0;
        // Metoda czysto wirtualna odpowiedzialna za rysowanie stanu.

        virtual void Pause(){};
        // Metoda wirtualna, która obsługuje pauzę w grze.
        // Domyślna implementacja nie wykonuje żadnych działań.
        // Może być nadpisana przez podklasy State w celu dostarczenia własnej implementacji pauzy.

        virtual void Start(){};
        // Metoda wirtualna, która obsługuje rozpoczęcie gry.
        // Domyślna implementacja nie wykonuje żadnych działań.
        // Może być nadpisana przez podklasy State w celu dostarczenia własnej implementacji rozpoczęcia gry.
    };
}

#endif // STATE_H
