#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "Plane.hpp"
#include "Enemy.hpp"
#include <iostream>
#include <memory>
#include <set>

GameState::GameState() : m_plane(), m_scoreboard(), m_grid() {
    // Initialize the plane, the scoreboard and the grid
    // Create 5 enemies
    for (int i = 0; i < 5; i++){
        auto enemy = std::make_shared<Enemy>(sf::Vector2f(50.f,50.f));
        // adding their pointers to the grid that takes care of collision detection
        m_grid.Insert(enemy);
        // adding their pointers to the objects vector that takes care of rendering
        m_objects.push_back(enemy);
    }
}

void GameState::Update(float timestep, sf::RenderWindow& l_window) {

    m_plane.Update(timestep, l_window);
    // Check the collisions in this loop
    for (int j = 0; j < m_plane.m_bullets.size() ; j++) {
        std::set<std::shared_ptr<GameObject>> possibleCollisions{m_grid.GetCollisions(m_plane.m_bullets[j])};
        for (auto i=possibleCollisions.begin() ; i != possibleCollisions.end(); i++) {
            if ((*i)->Collide(m_plane.m_bullets[j])) {
                (*i)->SetAlive(false);
                m_plane.m_bullets[j]->SetAlive(false);
                m_grid.Remove(*i);
            }
        }
    }
    // Remove the bullets that have collided and are not alive anymore
    for (int i= m_plane.m_bullets.size() - 1 ; i > -1 ; i--) {
        if (!m_plane.m_bullets[i]->IsAlive()) {
            m_plane.m_bullets.erase(m_plane.m_bullets.begin() + i);
        }
    }
    // Remove the enemies from the list that have collided with bullets and are not alive anymore
    for (int i= m_objects.size() - 1; i > -1 ; i--) {
        if (!m_objects[i]->IsAlive()) {
            m_objects.erase(m_objects.begin() + i);
        }
    }
    m_scoreboard.Update(timestep);
}

void GameState::Render(sf::RenderWindow& l_window) {
    // m_grid.Render(l_window);
    m_plane.Render(l_window);
    m_scoreboard.Render(l_window);
    // Render the enemies
    // Rendering them here assures us that they are rendered only once
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