#pragma once

#include <SFML/Graphics.hpp>
#include "Plane.hpp"
#include "Enemy.hpp"
#include "Scoreboard.hpp"
#include "State.hpp"
#include "Quadtree.hpp"

class GameState : public State{
public:
    GameState();

    void Update(float timestep, sf::RenderWindow& l_window);
    void Render(sf::RenderWindow& l_window);
    void HandleInput();
    void Restart();
    void Respawn();
    int GetCount();
private:
    Plane m_plane;
    Scoreboard m_scoreboard;
    Quad m_quad;
};