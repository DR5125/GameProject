#include "StateManager.h"

Engine::StateMan::StateMan() : m_add(false), m_replace(false), m_remove(false) {}

Engine::StateMan::~StateMan() {}

void Engine::StateMan::Add(std::unique_ptr<State> toAdd, bool replace) // Służy do dodawania nowego stanu do menedżera stanów.
{                                                                      // Przyjmuje unikalny wskaźnik toAdd do obiektu stanu,
    m_add = true;                                                      // który ma zostać dodany, oraz flagę replace, która określa,
    m_newState = std::move(toAdd);                                     // czy nowy stan ma zastąpić aktualny stan na szczycie stosu.

    m_replace = replace;
}

void Engine::StateMan::PopCurrent() // Wsuwa aktualny stan ze stosu. Ustawia flagę m_remove na true, co oznacza żądanie usunięcia aktualnego stanu.
{
    m_remove = true;
}

void Engine::StateMan::ProcessStateChange()
{
    if (m_remove && (!m_stateStack.empty())) // Jeśli żądano usunięcia aktualnego stanu i stos stanów nie jest pusty
    {
        m_stateStack.pop(); // Usuń aktualny stan ze stosu

        if (!m_stateStack.empty()) // Jeśli stos stanów nie jest pusty po usunięciu
        {
            m_stateStack.top()->Start(); // Uruchom nowy stan na szczycie stosu
        }

        m_remove = false; // Zresetuj flagę usunięcia
    }

    if (m_add) // Jeśli żądano dodania nowego stanu
    {
        if (m_replace && (!m_stateStack.empty())) // Jeśli żądano zastąpienia aktualnego stanu i stos stanów nie jest pusty
        {
            m_stateStack.pop(); // Usuń aktualny stan ze stosu
            m_replace = false; // Zresetuj flagę zastąpienia
        }

        if (!m_stateStack.empty()) // Jeśli stos stanów nie jest pusty po usunięciu
        {
            m_stateStack.top()->Pause(); // Wstrzymaj działanie aktualnego stanu
        }

        m_stateStack.push(std::move(m_newState)); // Dodaj nowy stan na stos
        m_stateStack.top()->Init(); // Zainicjalizuj nowy stan
        m_stateStack.top()->Start(); // Uruchom nowy stan
        m_add = false; // Zresetuj flagę dodania
    }
}

std::unique_ptr<Engine::State> &Engine::StateMan::GetCurrent()
{
    return m_stateStack.top(); // Zwróć referencję do aktualnego stanu na szczycie stosu
}
