#ifndef STATEMAN_H
#define STATEMAN_H

#include <stack>
#include <memory>

#include <State.h>

/*
 * Klasa "StateMan" umożliwia łatwe zarządzanie stanami w grze,
 * dodawanie nowych stanów, usuwanie bieżącego stanu oraz kontrolowanie kolejności wyświetlania i aktualizacji stanów.
 */

namespace Engine
{
    class StateMan
    {
        public:
            StateMan();
            // Konstruktor klasy StateMan.

            ~StateMan();
            // Destruktor klasy StateMan.

            void Add(std::unique_ptr<State> toAdd, bool replace = false);
            // Dodaje stan do stosu stanów.
            // Argumenty:
            // - toAdd: wskaźnik na obiekt stanu do dodania.
            // - replace: flaga określająca, czy należy zastąpić bieżący stan nowym stanem (domyślnie false).

            void PopCurrent();
            // Usuwa bieżący stan ze stosu stanów.

            void ProcessStateChange();
            // Obsługuje zmianę stanu.
            // Jeśli istnieje nowy stan do dodania lub usuwany jest bieżący stan, metoda wykonuje odpowiednie operacje na stosie stanów.

            std::unique_ptr<State> &GetCurrent();
            // Zwraca referencję do bieżącego stanu.
            // Zwracana wartość:
            // - Referencja do wskaźnika na obiekt bieżącego stanu.

        private:
            std::stack<std::unique_ptr<State>> m_stateStack;
            // Stos przechowujący wskaźniki na obiekty stanów.
            // Stan na szczycie stosu jest bieżącym stanem.

            std::unique_ptr<State> m_newState;
            // Wskaźnik na nowy stan do dodania.

            bool m_add;
            // Flaga określająca, czy należy dodać nowy stan.

            bool m_replace;
            // Flaga określająca, czy należy zastąpić bieżący stan nowym stanem.

            bool m_remove;
            // Flaga określająca, czy należy usunąć bieżący stan.
    };

}
#endif // STATEMAN_H
