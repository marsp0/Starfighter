#pragma once

#include <SFML/Graphics.hpp>
#include "Healthbar.hpp"

class Enemy : public sf::RectangleShape {
    public:
        Enemy(sf::Vector2f l_size);
        ~Enemy();

        void Update(float timestep);
        void Render(sf::RenderWindow& l_window);

        sf::Vector2f getPosition();
        sf::Vector2f getSize();

        void TakeDamage(int l_damage);

        bool m_alive;

    private:
        
        sf::RectangleShape m_body;
        Healthbar m_healthBar;
        
        
};