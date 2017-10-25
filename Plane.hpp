#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.hpp"

class Plane : public sf::CircleShape {
public:
    Plane();
    ~Plane();

    void Update(float timestep);
    void Render(sf::RenderWindow& l_window);
    void HandleInput();
    float x();
    float y();
    float Left();
    float Right();
    float Top();
    float Bottom();
    void Move(float timestep);
    void Shoot(float timestep);
private:
    sf::Vector2f m_velocity;
    float m_planeVelocity;
    std::vector<Bullet> m_bullets;
};