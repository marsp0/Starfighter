#include <SFML/Graphics.hpp>
#include "Quadtree.hpp"

Quad::Quad(int l_x, int l_y, int l_width, int l_height, int l_level) : m_x(l_x), m_y(l_y), m_width(l_width), m_height(l_height), m_level(l_level), m_maxLevel(5), m_boundingShape(sf::Vector2f(l_width,l_height)) {
    m_boundingShape.setPosition(m_x,m_y);
    m_boundingShape.setOutlineColor(sf::Color::Black);
    m_boundingShape.setOutlineThickness(1.f);
    m_boundingShape.setFillColor(sf::Color(255,255,255,255));
    if (m_level == m_maxLevel) {
        return;
    } else {
        m_subRegions.push_back(Quad(m_x,m_y,m_width/2.f, m_height/2, m_level + 1));
        m_subRegions.push_back(Quad(m_x+m_width/2.f,m_y,m_width/2.f,m_height/2.f, m_level + 1));
        m_subRegions.push_back(Quad(m_x+m_width/2.f, m_y + m_height/2.f, m_width/2.f, m_height/2.f, m_level + 1));
        m_subRegions.push_back(Quad(m_x, m_y + m_height/2.f, m_width/2.f, m_height/2.f, m_level + 1));
    }
}

void Quad::Insert(sf::RectangleShape& l_gameObject){
    if (m_level == m_maxLevel){
        m_objects.push_back(l_gameObject);
        return;
    }
    bool temp{false};
    for (int i=0; i < m_subRegions.size(); i++){
        if (m_subRegions[i].Contains(l_gameObject)) {
            m_subRegions[i].Insert(l_gameObject);
            temp = true;
            break;
        }
    }
    if (!temp) {
        m_objects.push_back(l_gameObject);
    }
}

bool Quad::Contains(sf::RectangleShape& l_gameObject) {
    // for now lets try to use it only on rectangles as 
    // it assumes a bunch of stuff
    return (m_x <= l_gameObject.getPosition().x || m_x+m_width >= l_gameObject.getPosition().x + l_gameObject.getGlobalBounds().width  || \
            m_y <= l_gameObject.getPosition().y || m_y+m_height >= l_gameObject.getPosition().y + l_gameObject.getGlobalBounds().height );
}

void Quad::Render(sf::RenderWindow& l_window) {
    l_window.draw(m_boundingShape);
    for (int i =0; i < m_subRegions.size() ; i++) {
        m_subRegions[i].Render(l_window);
    }
}