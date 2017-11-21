#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "MenuState.hpp"

class Game {
public:
    Game();
    ~Game();

    void HandleInput();
    void Update(float timestep, sf::RenderWindow& l_window);
    void Render();
    void Run();
    void RestartClock();
    void Restart();
    sf::RenderWindow* GetWindow();

    void ChangeState();
private:
    GameState m_gameState;
    MenuState m_menuState;
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    double m_elapsed;
    State *m_currentState;
};