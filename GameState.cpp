#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "Plane.hpp"
#include "Enemy.hpp"
#include <iostream>

GameState::GameState() : m_plane() {
    for (int i=0; i < 5; i++){
        Enemy temp(sf::Vector2f(50.f,50.f));
        m_enemies.push_back(temp);
    }
}

GameState::~GameState() {

}

void GameState::Update(float timestep, sf::RenderWindow& l_window) {
    m_plane.Update(timestep, l_window);
    // NOTE :Move the collision detection to the enemy object
    for (int i = 0; i < m_plane.m_bullets.size(); i++) {
        for (int j = 0; j < m_enemies.size(); j++) {
            // Check if the bullets intersect with the enemies vertically from the right
            if ( ( (m_plane.m_bullets[i].getGlobalBounds().left > m_enemies[j].getPosition().x) and (m_enemies[j].getPosition().x + m_enemies[j].getSize().x > m_plane.m_bullets[i].getGlobalBounds().left) ) or \
                ((m_plane.m_bullets[i].getGlobalBounds().left + m_plane.m_bullets[i].getGlobalBounds().width > m_enemies[j].getPosition().x) and ((m_enemies[j].getPosition().x + m_enemies[j].getSize().x) > m_plane.m_bullets[i].getGlobalBounds().left + m_plane.m_bullets[i].getGlobalBounds().width))) {
                    if ((m_enemies[j].getPosition().y < m_plane.m_bullets[i].getGlobalBounds().top) and (m_enemies[j].getPosition().y+m_enemies[j].getSize().y > m_plane.m_bullets[i].getGlobalBounds().top)){
                        m_enemies[j].TakeDamage(m_plane.m_bullets[i].m_damage);
                        if (!m_enemies[j].m_alive) {
                            m_enemies.erase(m_enemies.begin()+j);
                        }
                        m_plane.m_bullets.erase(m_plane.m_bullets.begin()+i);
                    }
                }
        }
    }
    if (m_enemies.size() < 5) {
        for (int i=0; i < 5 - m_enemies.size(); i++){
            Enemy temp(sf::Vector2f(50.f,50.f));
            m_enemies.push_back(temp);
        }
    }
}

void GameState::Render(sf::RenderWindow& l_window) {
    m_plane.Render(l_window);
    for (int i = 0 ; i < m_enemies.size(); i++) {
        // Call render method of enemy.
        m_enemies[i].Render(l_window);
    }
}

void GameState::HandleInput(){

}