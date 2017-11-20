#pragma once

#include <SFML/Graphics.hpp>

class Healthbar {
    public:
        Healthbar(sf::Vector2f l_position);

        void Update(float timestep);
        void Render(sf::RenderWindow& l_window);

        void setPosition(sf::Vector2f l_position);
        void TakeDamage(int l_damage);


    private:
        
        sf::RectangleShape m_currentHealth;
        sf::RectangleShape m_missingHealth;
        int m_health;
        

};