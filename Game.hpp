#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.hpp"

class Game {
public:
    Game();
    ~Game();

    void HandleInput();
    void Update(float timestep);
    void Render();
    void Run();
    void RestartClock();

    sf::RenderWindow* GetWindow();
private:
    GameState m_gameState;
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    double m_elapsed;

};