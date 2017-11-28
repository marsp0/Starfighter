#pragma once

#include <SFML/Graphics.hpp>

class Quad {
    public:
        Quad(int l_x, int l_y, int l_width, int l_height, int l_level);
        void Insert(sf::RectangleShape& l_gameObject);
        // GameObject* CheckCollisions();
        bool Contains(sf::RectangleShape& l_gameObject);
        void Render(sf::RenderWindow& l_window);
    private:
        int m_x;
        int m_y;
        int m_width;
        int m_height;
        int m_level;
        int m_maxLevel;
        std::vector<sf::RectangleShape> m_objects;
        std::vector<Quad> m_subRegions;
        sf::RectangleShape m_boundingShape;
};
