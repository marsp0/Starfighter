#include "Grid.hpp"
#include <set>

Grid::Grid() : m_objects(10, std::vector<Cell>()) {
    
    // The grid is composed of a vector of vectors
    //  it is a 10 x 10. 80px wide and 60px high
    for (int i=0 ; i < 10 ; i++) {
        for (int j = 0; j < 10 ; j++) {
            
            m_objects[i].push_back(Cell(i*80,j*60, i*80 + 80, j*60+60));
        }
    }
}

void Grid::Render(sf::RenderWindow& l_window) {
    // Renders each cell - for now its only the boundries for debugging purposes
    for (int i = 0; i < m_objects.size(); i++) {
        for (int j=0; j < m_objects[i].size(); j++) {
            m_objects[i][j].Render(l_window);
        }
    }
}

std::set<std::shared_ptr<GameObject> > Grid::GetCollisions(std::shared_ptr<GameObject> l_gameObject){
    // Gets the list of elements that might be colliding with the passed object. Usually a bullet, but it can be extended later
    // cells is a vector containig the positions(indices) of the cells that contain the passed game object
    std::set<std::pair<int,int> > cells{GetIndices(l_gameObject)};
    std::set<std::shared_ptr<GameObject> > result;
    for (auto i = cells.begin() ; i != cells.end(); i++) {
        if ((*i).second > -1 && (*i).second < 10 && (*i).first > -1 && (*i).first < 10) {
            result.insert(m_objects[(*i).second][(*i).first].m_objects.begin(), m_objects[(*i).second][(*i).first].m_objects.end() );
        }
    }
    return result;
}
   
void Grid::Insert(std::shared_ptr<GameObject> l_gameObject) {
    std::set<std::pair<int,int> > indices{GetIndices(l_gameObject)};
    for (auto i = indices.begin(); i != indices.end() ; i++) {
        m_objects[(*i).second][(*i).first].Insert(l_gameObject);
    }
}

void Grid::Remove(std::shared_ptr<GameObject> l_gameObject) {
    std::set<std::pair<int,int> > indices{GetIndices(l_gameObject)};
    for (auto i = indices.begin(); i != indices.end() ; i++){
        m_objects[(*i).second][(*i).first].Remove(l_gameObject);
    }
}

std::set<std::pair<int,int> > Grid::GetIndices(std::shared_ptr<GameObject> l_gameObject) {
    // This might happen when the entire object is in one cell
    std::set<std::pair<int,int> > result;
    result.insert(std::make_pair(l_gameObject->Left() / 80, l_gameObject->Top() / 60));
    result.insert(std::make_pair(l_gameObject->Right()/ 80, l_gameObject->Top() / 60));
    result.insert(std::make_pair(l_gameObject->Right()/ 80, l_gameObject->Bottom()/ 60));
    result.insert(std::make_pair(l_gameObject->Left() / 80, l_gameObject->Bottom()/ 60));
    return result;
}