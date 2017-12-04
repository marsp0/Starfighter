#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "Plane.hpp"
#include "Enemy.hpp"
#include <iostream>

GameState::GameState() : m_plane(), m_scoreboard(), m_quad(0,0,800,600,1) {
    // Initialize the plane and the scoreboard
    // Create 5 enemies
    for (int i=0; i < 5; i++){
        Enemy* temp = new Enemy(sf::Vector2f(50.f,50.f));
        m_quad.Insert(temp);
    }
}

void GameState::Update(float timestep, sf::RenderWindow& l_window) {
    m_plane.Update(timestep, l_window);
    std::vector<int> toRemove;
    for (int i=0; i < m_plane.m_bullets.size(); i++) {
        
        std::vector<GameObject*> possibleCollisions{m_quad.Retrieve(&(m_plane.m_bullets[i]))};
        for (int j =0; j < m_plane.m_bullets.size() ; j++) {
            for (int i =0 ; i < possibleCollisions.size(); i++) {
                if (possibleCollisions[i]->Collide(&(m_plane.m_bullets[j]))) {
                    for (int k = 0 ; k < possibleCollisions[i]->parent->m_objects.size() ; k++) {
                        printf("dsa\n");
                        if (possibleCollisions[i]->parent->m_objects[k] == possibleCollisions[i]) {
                            delete possibleCollisions[i];
                            possibleCollisions.erase(possibleCollisions.begin() + i);
                            possibleCollisions[i]->parent->m_objects.erase(possibleCollisions[i]->parent->m_objects.begin() + k);
                        }
                    }
                    printf("123\n");
                    
                    m_plane.m_bullets.erase(m_plane.m_bullets.begin() + j);
                }
            }
        }
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
    Enemy* temp = new Enemy(sf::Vector2f(50.f,50.f));
    m_quad.Insert(temp);
}