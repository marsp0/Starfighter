#include <SFML/Graphics.hpp>
#include "Quadtree.hpp"
#include <iostream>
#include "GameObject.hpp"

Quad::Quad(int l_x, int l_y, int l_width, int l_height, int l_level) : m_x(l_x), m_y(l_y), m_width(l_width), m_height(l_height), m_level(l_level), m_boundingShape(sf::Vector2f(l_width,l_height)) {
    m_boundingShape.setPosition(m_x,m_y);
    m_boundingShape.setOutlineColor(sf::Color::Black);
    m_boundingShape.setOutlineThickness(1.f);
    m_boundingShape.setFillColor(sf::Color::Transparent);
    if (m_level == m_maxLevel) {
        return;
    }
}

void Quad::Insert(GameObject* l_gameObject) {
    m_objects.push_back(l_gameObject);
    l_gameObject->parent = this;
    // printf("Current recursion level is %u, the subregion is %u - %u and the size of the objects here is %u\n", m_level,m_x, m_y, m_objects.size());
    if (m_objects.size() > 5 || m_subRegions.size() > 0) {
        if (m_subRegions.size() == 0) {
            m_subRegions.push_back(Quad(m_x,m_y,m_width/2.f, m_height/2, m_level + 1));
            m_subRegions.push_back(Quad(m_x+m_width/2.f,m_y,m_width/2.f,m_height/2.f, m_level + 1));
            m_subRegions.push_back(Quad(m_x+m_width/2.f, m_y + m_height/2.f, m_width/2.f, m_height/2.f, m_level + 1));
            m_subRegions.push_back(Quad(m_x, m_y + m_height/2.f, m_width/2.f, m_height/2.f, m_level + 1));
        }
        std::vector<int> temp;
        for (int i=0; i < m_objects.size(); i++){
            for (int j=0; j< m_subRegions.size(); j++) {
                if (m_subRegions[j].Contains(m_objects[i])) {
                    m_subRegions[j].Insert(m_objects[i]);
                    temp.push_back(i);
                    break;
                }
            }
        }
        for (int i = temp.size()-1; i > -1; i--){
            // Delete the elements that we pushed further from the current level
            if (m_objects.size() > 0) {
                m_objects.erase(m_objects.begin() + temp[i]);
            }
        }
    }
}   

bool Quad::Contains(GameObject* l_gameObject) {
    return (m_x <= l_gameObject->GetPosition().x && m_x+m_width >= l_gameObject->GetPosition().x + l_gameObject->GetGlobalBounds().width  && \
            m_y <= l_gameObject->GetPosition().y && m_y+m_height >= l_gameObject->GetPosition().y + l_gameObject->GetGlobalBounds().height );
}

void Quad::Render(sf::RenderWindow& l_window) {
    l_window.draw(m_boundingShape);
    
    for (int i =0; i < m_subRegions.size() ; i++) {
        m_subRegions[i].Render(l_window);
    }
    for (int i =0; i < m_objects.size(); i++) {
        m_objects[i]->Render(l_window);
    }
}

void Quad::Update(float timestep) {

}

int Quad::GetIndex(GameObject* l_gameObject) {
    int index{-1};
    float verticalMidpoint{m_x + m_width/2};
    float horisontalMidpoint{m_y + m_height/2};

    bool topQuadrant{horisontalMidpoint > l_gameObject->Bottom()};
    bool bottomQuadrant{horisontalMidpoint < l_gameObject->Top()};

    if (l_gameObject->Right() < verticalMidpoint) {
        if (topQuadrant) {
            index = 1;
        } else if (bottomQuadrant) {
            index = 4;
        }
    } else if (l_gameObject->Left() > verticalMidpoint) {
        if (topQuadrant) {
            index = 2;
        } else if (bottomQuadrant) {
            index = 3;
        }
    }
    return index;
}

std::vector<GameObject*> Quad::Retrieve(GameObject* l_gameObject) {
    int index{GetIndex(l_gameObject)};
    std::vector<GameObject*> returnObjects;
    if (index != -1 and m_subRegions.size() > 0) {
        std::vector<GameObject*> newVector{m_subRegions[index].Retrieve(l_gameObject)};
        returnObjects.insert(returnObjects.end(), newVector.begin(), newVector.end());
    }
    returnObjects.insert(returnObjects.end(), m_objects.begin(), m_objects.end());
    return returnObjects;
}