#include <SFML/Graphics.hpp>
#include "Game.hpp"

Game::Game() : m_gameState(), m_window(sf::VideoMode(800,600,32), "StarShooter", sf::Style::Titlebar | sf::Style::Close){
    m_clock.restart();
    m_elapsed = 0.0f;
    m_window.setFramerateLimit(60);
}

Game::~Game() {

}

void Game::Update(float timestep) {
    m_gameState.Update(timestep);
}

void Game::Render() {
    m_window.clear(sf::Color(sf::Color(150,207,234)));
    m_gameState.Render(*GetWindow());
    m_window.display();
}

void Game::HandleInput() {
    sf::Event event;
    while(m_window.pollEvent(event)) {
        if (sf::Event::EventType::Closed == event.type) {
            m_window.close();
        }
    }
}

void Game::Run() {
    float timestep = 1.0/60.f;
    while (m_window.isOpen()) {

        HandleInput();
        while (m_elapsed >= timestep) {
            Update(timestep);
            m_elapsed -= timestep;
        }
        Render();
        RestartClock();
    }
}

void Game::RestartClock() {
    m_elapsed += m_clock.restart().asSeconds();
}

sf::RenderWindow* Game::GetWindow() {
    return &m_window;
}