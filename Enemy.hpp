#pragma once

#include <SFML/Graphics.hpp>
#include "Healthbar.hpp"
#include "Bullet.hpp"
#include "Plane.hpp"

class Enemy : public sf::RectangleShape {
    public:
        Enemy(sf::Vector2f l_size);

        void Update(float timestep);
        void Render(sf::RenderWindow& l_window);
        sf::Vector2f getPosition();
        sf::Vector2f getSize();
        void TakeDamage(int l_damage);
        bool IsAlive();
        bool Collide(Bullet& l_bullet);
        bool Collide(Plane& l_plane);

    private:
        
        sf::RectangleShape m_body;
        Healthbar m_healthBar;
        bool m_alive;
        
};