#pragma once

#include <SFML/Graphics.hpp>

class Button {
    public:
        Button(sf::Vector2f l_size, sf::Vector2f l_position,  sf::String l_title);

        void Update(float timestep);
        void Render(sf::RenderWindow& l_window);

        sf::FloatRect GetGlobalBounds();
    private:
        sf::Text m_text;
        sf::Font m_font;
        sf::RectangleShape m_background;
};