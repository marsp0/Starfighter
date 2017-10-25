#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "Plane.hpp"

GameState::GameState() : m_plane() {

}

GameState::~GameState() {

}

void GameState::Update(float timestep) {
    m_plane.Update(timestep);
}

void GameState::Render(sf::RenderWindow& l_window) {
    m_plane.Render(l_window);
}

void GameState::HandleInput(){

}