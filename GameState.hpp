#pragma once

#include <SFML/Graphics.hpp>
#include "Plane.hpp"
class GameState {
public:
    GameState();
    ~GameState();

    void Update(float timestep);
    void Render(sf::RenderWindow& l_window);
    void HandleInput();
private:
    Plane m_plane;
    std::vector<sf::RectangleShape> m_enemies;
};