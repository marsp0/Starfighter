#pragma once

#include <SFML/Graphics.hpp>
#include "Plane.hpp"
#include "Enemy.hpp"
#include "Scoreboard.hpp"
#include "State.hpp"


class GameState : public State{
public:
    GameState();
    ~GameState();

    void Update(float timestep, sf::RenderWindow& l_window);
    void Render(sf::RenderWindow& l_window);
    void HandleInput();
private:
    Plane m_plane;
    std::vector<Enemy> m_enemies;
    Scoreboard m_scoreboard;
};