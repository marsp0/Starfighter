#include "Grid.hpp"

Grid::Grid() {

    for (int i=0 ; i < 10 ; i++) {
        m_objects.push_back(std::vector<Cell>());
        for (int j = 0; j < 10 ; j++) {
            m_objects[i].push_back(Cell(i*80,j*60, i*80 + 80, j*60+60));
        }
    }
}

void Grid::Render(sf::RenderWindow& l_window) {
    for (int i = 0; i < m_objects.size(); i++) {
        for (int j=0; j < m_objects[i].size(); j++) {
            m_objects[i][j].Render(l_window);
        }
    }
}

std::vector<std::shared_ptr<GameObject> > GetCollisions(std::shared_ptr<GameObject>){

}
   
void Grid::Insert(std::shared_ptr<GameObject> l_gameObject) {
    std::vector<std::pair<int,int> > indices{GetIndices(l_gameObject)};
    for (int i = 0; i < indices.size() ; i++) {
        m_objects[indices[i].second][indices[i].first].Insert(l_gameObject);
    }
}

void Remove(std::shared_ptr<GameObject> l_gameObject) {

}

std::vector<std::pair<int,int> > GetIndices(std::shared_ptr<GameObject> l_gameObject) {
    // TODO : Make sure we are not adding duplicate cells
    // This might happen when the entire object is in one cell
    std::vector<std::pair<int,int> > result;
    result.push_back(std::make_pair(l_gameObject->Left() / 80, l_gameObject->Top() / 60));
    result.push_back(std::make_pair(l_gameObject->Right()/ 80, l_gameObject->Top() / 60));
    result.push_back(std::make_pair(l_gameObject->Right()/ 80, l_gameObject->Bottom()/ 60));
    result.push_back(std::make_pair(l_gameObject->Left() / 80, l_gameObject->Bottom()/ 60));
}