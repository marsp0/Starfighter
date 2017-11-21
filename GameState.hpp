#pragma once

#include <SFML/Graphics.hpp>
#include "Plane.hpp"
#include "Enemy.hpp"

class GameState {
public:
    GameState();
    ~GameState();

    void Update(float timestep, sf::RenderWindow& l_window);
    void Render(sf::RenderWindow& l_window);
    void HandleInput();
private:
    Plane m_plane;
    std::vector<Enemy> m_enemies;
};