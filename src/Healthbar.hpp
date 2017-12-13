#pragma once

#include <SFML/Graphics.hpp>

class Healthbar {
    public:
        Healthbar(sf::Vector2f l_position);

        void Update(float timestep);
        void Render(sf::RenderWindow& l_window);

        void setPosition(sf::Vector2f l_position);
        void setSize(sf::Vector2f l_size);
        bool TakeDamage(int l_damage);

        // NOTE : check pros and cons of initializing vars in different ways.
        static constexpr float HP_WIDTH{50.f};
        static constexpr float HP_HEIGHT{7.f};

    private:
        
        sf::RectangleShape m_currentHealth;
        sf::RectangleShape m_missingHealth;
        int m_health;
        float m_width;
        float m_height;

};