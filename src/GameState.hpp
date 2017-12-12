#pragma once

#include <SFML/Graphics.hpp>
#include "Plane.hpp"
#include "Enemy.hpp"
#include "Scoreboard.hpp"
#include "State.hpp"
#include "Grid.hpp"

class GameState : public State{
public:
    GameState();

    void Update(float timestep, sf::RenderWindow& l_window);
    void Render(sf::RenderWindow& l_window);
    void HandleInput();
    void Restart();
    void Respawn();
private:
    Plane m_plane;
    Scoreboard m_scoreboard;
    Grid m_grid;
    std::vector<std::shared_ptr<GameObject>> m_objects;
};