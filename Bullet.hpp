#pragma once

#include <SFML/Graphics.hpp>

class Bullet : public sf::CircleShape {
public:
    Bullet(sf::Vector2f l_position);
    ~Bullet();

    bool Update(float timestep);

    void getPosition();

    float Top();
    float Bottom();
    float Left();
    float Right();
private:
    float m_velocity;
};