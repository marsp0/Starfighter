#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>

class Bullet : public sf::CircleShape {
public:
    Bullet(sf::Vector2f l_position, float x_direction, float y_direction);
    ~Bullet();

    bool Update(float timestep);

    sf::Vector2f getPosition();

    float Top();
    float Bottom();
    float Left();
    float Right();
    std::chrono::time_point<std::chrono::system_clock> GetSpawnTime();
    void IncreaseDamage(int l_damage);
    void DecreaseDamage(int l_damage);
    void SetDamage(int l_damage);
    int GetDamage();
    int m_damage;

private:
    float m_velocity;
    std::chrono::time_point<std::chrono::system_clock> m_spawnTime;
    sf::Vector2f m_direction;
    
};