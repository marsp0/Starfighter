#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "Plane.hpp"
#include "Enemy.hpp"
#include <iostream>
#include <memory>

GameState::GameState() : m_plane(), m_scoreboard(), m_quad(0,0,800,600,1) {
    // Initialize the plane and the scoreboard
    // Create 5 enemies
    for (int i=0; i < 5; i++){
        auto enemy = std::make_shared<Enemy>(sf::Vector2f(50.f,50.f));
        m_quad.Insert(enemy);
    }
}

void GameState::Update(float timestep, sf::RenderWindow& l_window) {
    m_plane.Update(timestep, l_window);
    std::vector<int> toRemove;
    
    for (int j = 0; j < m_plane.m_bullets.size() ; j++) {
        std::vector<std::shared_ptr<GameObject> > possibleCollisions{m_quad.Retrieve(m_plane.m_bullets[j])};
        for (int i =0 ; i < possibleCollisions.size(); i++) {
            if (possibleCollisions[i]->Collide(m_plane.m_bullets[j])) {
                m_quad.Remove(possibleCollisions[i]);
                toRemove.push_back(j);
            }
        }
    }
    for (int i = toRemove.size()-1 ; i > -1; i--) {
        m_plane.m_bullets.erase(m_plane.m_bullets.begin() + toRemove[i]);
    }
    m_scoreboard.Update(timestep);
}

void GameState::Render(sf::RenderWindow& l_window) {
    m_quad.Render(l_window);
    m_plane.Render(l_window);
    m_scoreboard.Render(l_window);
    
}

void GameState::HandleInput(){

}

void GameState::Restart() {
    // for (int i=0; i < 5; i++){
    //     Enemy* temp = new Enemy(sf::Vector2f(50.f,50.f));
    //     m_quad.Insert(temp);
    // }
    m_plane.Restart();
    m_scoreboard.Restart();
}

void GameState::Respawn() {
    auto enemy = std::make_shared<Enemy>(sf::Vector2f(50.f,50.f));
    m_quad.Insert(enemy);
}

int GameState::GetCount() {
    
    return m_quad.GetCount();
}