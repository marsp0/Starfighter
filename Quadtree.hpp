#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include <iostream>

class GameObject;

class Quad {
    public:
        Quad(int l_x, int l_y, int l_width, int l_height, int l_level);
        void Insert(GameObject* l_gameObject);
        bool Contains(GameObject* l_gameObject);
        void Render(sf::RenderWindow& l_window);
        void Update(float timestep);
        int GetIndex(GameObject* l_gameObject);
        std::vector<GameObject*> Retrieve(GameObject* l_gameObject);
        void Clear();
        std::vector<GameObject*> m_objects;
        
    private:
        int m_x;
        int m_y;
        int m_width;
        int m_height;
        int m_level;
        int m_maxLevel;
        
        std::vector<Quad> m_subRegions;
        sf::RectangleShape m_boundingShape;
};