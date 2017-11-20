#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "Plane.hpp"
#include <iostream>

GameState::GameState() : m_plane() {
    for (int i=0; i < 5; i++){
        sf::RectangleShape temp;
        temp.setOutlineThickness(2.f);
        temp.setOutlineColor(sf::Color::Black);
        temp.setPosition((float)(rand()%800 + 1), (float)(rand()%100));
        temp.setFillColor(sf::Color::Yellow);
        temp.setSize(sf::Vector2f(50.f,50.f));
        m_enemies.push_back(temp);
    }
}

GameState::~GameState() {

}

void GameState::Update(float timestep) {
    m_plane.Update(timestep);
}

void GameState::Render(sf::RenderWindow& l_window) {
    m_plane.Render(l_window);
    for (int i = 0 ; i < m_enemies.size(); i++) {
        l_window.draw(m_enemies[i]);
    }
}

void GameState::HandleInput(){

}