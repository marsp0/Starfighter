#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "Plane.hpp"
#include "Enemy.hpp"
#include <iostream>

GameState::GameState() : m_plane(), m_scoreboard(), m_quad(0,0,800,600,1) {
    // Initialize the plane and the scoreboard
    // Create 5 enemies
    for (int i=0; i < 5; i++){
        Enemy temp(sf::Vector2f(50.f,50.f));
        m_enemies.push_back(temp);
    }
}

void GameState::Update(float timestep, sf::RenderWindow& l_window) {
    m_plane.Update(timestep, l_window);
    // For each bullet we check if it collides with one of the enemies
    // On(2)
    for (int i = 0; i < m_plane.m_bullets.size(); i++) {
        for (int j = 0; j < m_enemies.size(); j++) {
            if (m_enemies[j].Collide(m_plane.m_bullets[i])){
                m_plane.m_bullets.erase(m_plane.m_bullets.begin()+i);
                if (!m_enemies[j].IsAlive()) {
                    m_enemies.erase(m_enemies.begin()+j);
                    m_scoreboard.AddScore(10);
                }
            }
        }
    }
    // We respawn a new enemie if we have less than 5 on screen
    if (m_enemies.size() < 5) {
        for (int i=0; i < 5 - m_enemies.size(); i++){
            Enemy temp(sf::Vector2f(50.f,50.f));
            m_enemies.push_back(temp);
        }
    }
    m_scoreboard.Update(timestep);
}

void GameState::Render(sf::RenderWindow& l_window) {
    m_quad.Render(l_window);
    m_plane.Render(l_window);
    for (int i = 0 ; i < m_enemies.size(); i++) {
        m_enemies[i].Render(l_window);
    }
    m_scoreboard.Render(l_window);
}

void GameState::HandleInput(){

}

void GameState::Restart() {
    m_enemies.clear();
    for (int i=0; i < 5; i++){
        Enemy temp(sf::Vector2f(50.f,50.f));
        m_enemies.push_back(temp);
    }
    m_plane.Restart();
    m_scoreboard.Restart();
}