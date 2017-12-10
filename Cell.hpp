#pragma once
#include <memory>
#include "GameObject.hpp"
class Cell {

    public:

        Cell(int l_x, int l_y, int l_width, int l_height);
        void Insert(std::shared_ptr<GameObject> l_gameObject);
        void Remove(std::shared_ptr<GameObject> l_gameObject);
        void Render(sf::RenderWindow& l_window);

    protected:
        int m_x;
        int m_y;
        int m_width;
        int m_height;
        sf::RectangleShape m_background;
        std::vector<std::shared_ptr<GameObject> > m_objects;
};