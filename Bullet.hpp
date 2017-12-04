#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include "GameObject.hpp"

class Bullet : public GameObject {
public:
    Bullet(sf::Vector2f l_position, float x_direction, float y_direction);
    ~Bullet();

    bool Update(float timestep);
    void Render(sf::RenderWindow& l_window);
    sf::Vector2f GetPosition();
    sf::FloatRect GetGlobalBounds();

    int Top();
    int Bottom();
    int Left();
    int Right();
    std::chrono::time_point<std::chrono::system_clock> GetSpawnTime();
    void IncreaseDamage(int l_damage);
    void DecreaseDamage(int l_damage);
    void SetDamage(int l_damage);
    int GetDamage();
    bool Collide(GameObject* l_gameObject);
    int m_damage;

private:
    float m_velocity;
    std::chrono::time_point<std::chrono::system_clock> m_spawnTime;
    sf::Vector2f m_direction;
    sf::CircleShape m_body;
    
};