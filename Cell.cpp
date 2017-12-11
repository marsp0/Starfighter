#include "Cell.hpp"

Cell::Cell(int l_x, int l_y, int l_width, int l_height) : 
    m_x(l_x),
    m_y(l_y),
    m_width(l_width),
    m_height(l_height),
    m_background(sf::Vector2f(l_width, l_height)),
    m_objects() {

        m_background.setFillColor(sf::Color::Transparent);
        m_background.setPosition(sf::Vector2f(m_x,m_y));
        m_background.setOutlineColor(sf::Color::Black);
        m_background.setOutlineThickness(1.f);
}

void Cell::Insert(std::shared_ptr<GameObject> l_gameObject) {
    m_objects.push_back(l_gameObject);
}

void Cell::Remove(std::shared_ptr<GameObject> l_gameObject) {
    for (int i=0; i < m_objects.size(); i++) {
        if (m_objects[i] == l_gameObject) {
            m_objects.erase(m_objects.begin() + i);
        }
    }
}

void Cell::Render(sf::RenderWindow& l_window) {
    l_window.draw(m_background);
    for (int i = 0; i < m_objects.size(); i++) {
        if (m_objects[i]-> m_toRender) {
            m_objects[i]->Render(l_window);
            m_objects[i]-> m_toRender = false;
        }
    }
}