#pragma once

#include <SFML/Graphics.hpp>

class Enemy : public sf::RectangleShape {
    public:
        Enemy();
        ~Enemy();

        void Update(float timestep);
        void Render(sf::RenderWindow& l_window);

    private:
        
};