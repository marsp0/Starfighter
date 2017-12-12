#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "Plane.hpp"
#include "Enemy.hpp"
#include <iostream>
#include <memory>
#include <set>

GameState::GameState() : m_plane(), m_scoreboard(), m_grid() {
    // Initialize the plane and the scoreboard
    // Create 5 enemies
    for (int i = 0; i < 5; i++){
        auto enemy = std::make_shared<Enemy>(sf::Vector2f(50.f,50.f));
        
        m_grid.Insert(enemy);
        m_objects.push_back(enemy);
    }
}

void GameState::Update(float timestep, sf::RenderWindow& l_window) {
    m_plane.Update(timestep, l_window);
    std::vector<int> toRemove;
    
    for (int j = 0; j < m_plane.m_bullets.size() ; j++) {
        std::vector<std::shared_ptr<GameObject>> possibleCollisions{m_grid.GetCollisions(m_plane.m_bullets[j])};
        std::set<std::shared_ptr<GameObject>> result;
        for (int i=0; i < possibleCollisions.size() ; i++) {
            result.insert(possibleCollisions[i]);
        }
        for (auto i=result.begin() ; i != result.end(); i++) {
            if ((*i)->Collide(m_plane.m_bullets[j])) {
                (*i)->SetAlive(false);
                m_grid.Remove(*i);
                toRemove.push_back(j);
            }
        }
    }
    for (int i = toRemove.size()-1 ; i > -1; i--) {
        if (toRemove[i] < m_plane.m_bullets.size()) {
            m_plane.m_bullets.erase(m_plane.m_bullets.begin() + toRemove[i]);
        }
    }

    for (int i=0; i < m_objects.size() ; i++) {
        if (!m_objects[i]->IsAlive()) {
            m_objects.erase(m_objects.begin() + i);
        }
    }
    m_scoreboard.Update(timestep);
}

void GameState::Render(sf::RenderWindow& l_window) {
    m_grid.Render(l_window);
    m_plane.Render(l_window);
    m_scoreboard.Render(l_window);
    for (int i = 0; i < m_objects.size() ; i++) {
        if (m_objects[i]->IsAlive()) {
            m_objects[i]->Render(l_window);
        }
    }
}

void GameState::HandleInput(){

}

void GameState::Restart() {
    for (int i=0; i < 5; i++){
        auto enemy = std::make_shared<Enemy>(sf::Vector2f(50.f,50.f));
        m_grid.Insert(enemy);
        m_objects.push_back(enemy);
    }
    m_plane.Restart();
    m_scoreboard.Restart();
}

void GameState::Respawn() {
    auto enemy = std::make_shared<Enemy>(sf::Vector2f(50.f,50.f));
    m_grid.Insert(enemy);
    m_objects.push_back(enemy);
}