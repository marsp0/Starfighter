#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "MenuState.hpp"
#include "HighscoreState.hpp"

class Game {
public:
    Game();

    void HandleInput();
    void Update(float timestep, sf::RenderWindow& l_window);
    void Render();
    void Run();
    void RestartClock();
    void Restart();
    sf::RenderWindow* GetWindow();

    void ChangeState( State* l_state);
private:
    GameState m_gameState;
    MenuState m_menuState;
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    double m_elapsed;
    State *m_currentState;
    HighscoreState m_highscoreState;
};