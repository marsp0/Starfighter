#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "GameObject.hpp"
#include "Cell.hpp"
#include <set>

class Grid {
    public:
        
        Grid();

        void Render(sf::RenderWindow& l_window);
        std::set<std::shared_ptr<GameObject> > GetCollisions(std::shared_ptr<GameObject>);
        void Insert(std::shared_ptr<GameObject> l_gameObject);
        void Remove(std::shared_ptr<GameObject> l_gameObject);
        std::set<std::pair<int,int> > GetIndices(std::shared_ptr<GameObject> l_gameObject);
        std::vector<std::vector<Cell> > m_objects;

    protected:
        

};