#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include <iostream>
#include <memory>

class GameObject;

class Quad {
    public:
        Quad(int l_x, int l_y, int l_width, int l_height, int l_level);
        void Insert(std::shared_ptr<GameObject> l_gameObject);
        bool Contains(std::shared_ptr<GameObject> l_gameObject);
        void Render(sf::RenderWindow& l_window);
        void Update(float timestep);
        int GetIndex(std::shared_ptr<GameObject> l_gameObject);
        std::vector<std::shared_ptr<GameObject>> Retrieve(std::shared_ptr<GameObject> l_gameObject);
        void Clear();
        void Remove(std::shared_ptr<GameObject> l_gameObject);
        void BubbleUp(Quad* l_quad);
        int GetCount();

    public:
        std::vector<std::shared_ptr<GameObject> > m_objects;
        std::vector<Quad> m_subRegions;
        
    private:
        int m_x;
        int m_y;
        int m_width;
        int m_height;
        int m_level;
        int m_maxLevel;
        
        sf::RectangleShape m_boundingShape;
};