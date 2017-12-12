#pragma once

#include <SFML/Graphics.hpp>
#include "Healthbar.hpp"
#include "Bullet.hpp"
#include "Plane.hpp"
#include "GameObject.hpp"
#include <memory>

class Enemy : public GameObject {
    public:
        Enemy(sf::Vector2f l_size);

        void Update(float timestep);
        void Render(sf::RenderWindow& l_window);

        sf::Vector2f GetPosition();
        sf::FloatRect GetGlobalBounds();
        sf::Vector2f GetSize();
        void TakeDamage(int l_damage);
        bool IsAlive();
        void SetAlive(bool l_value);
        bool Collide(std::shared_ptr<GameObject> l_gameObject);
        int Top();
        int Bottom();
        int Left();
        int Right();

    private:
        
        sf::RectangleShape m_body;
        Healthbar m_healthBar;
        bool m_alive;
        
};