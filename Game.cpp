#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <iostream>

Game::Game() : m_gameState(), m_menuState(), m_highscoreState(), m_window(sf::VideoMode(800,600,32), "StarShooter", sf::Style::Titlebar | sf::Style::Close){
    Restart();
}

Game::~Game() {

}

void Game::Update(float timestep, sf::RenderWindow& l_window) {
    // NOTE : REMOVE THE WINDOW INSTANCE FROM THE UPDATE METHOD
    m_currentState->Update(timestep, l_window);
    if (m_currentState == &m_menuState) {
        if (m_menuState.m_buttonPressed[0]) {
            Restart();
            m_menuState.m_buttonPressed[0] = false;
        } else if (m_menuState.m_buttonPressed[1]) {
            ChangeState(&m_highscoreState);
            m_menuState.m_buttonPressed[1] = false;
        } else if (m_menuState.m_buttonPressed[2]) {
            m_window.close();
            m_menuState.m_buttonPressed[2] = false;
        }
    }
}

void Game::Render() {
    m_window.clear(sf::Color(sf::Color(150,207,234)));
    m_currentState->Render(*GetWindow());
    m_window.display();
    
}

void Game::HandleInput() {
    sf::Event event;
    while(m_window.pollEvent(event)) {
        if (sf::Event::EventType::Closed == event.type) {
            m_window.close();
        } else if (event.type == sf::Event::EventType::KeyPressed) {
            if (event.key.code == sf::Keyboard::Key::Escape){
                if (m_currentState == &m_highscoreState){
                    ChangeState(&m_menuState);
                } else if (m_currentState == &m_menuState) {
                    ChangeState(&m_gameState);
                } else {
                    ChangeState(&m_menuState);
                }
            }
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.key.code == sf::Mouse::Button::Left){
                if (m_currentState == &m_menuState) {
                    m_menuState.m_pressed = true;
                    m_menuState.m_mousePosition = sf::Mouse::getPosition(*GetWindow());
                }
            }
        }
    }
}

void Game::Run() {
    float timestep = 1.0/60.f;
    while (m_window.isOpen()) {

        HandleInput();
        while (m_elapsed >= timestep) {
            Update(timestep, *GetWindow());
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

void Game::ChangeState(State* l_state){
    m_currentState = l_state;
}

void Game::Restart() {
    m_clock.restart();
    m_elapsed = 0.0f;
    m_window.setFramerateLimit(90);
    m_currentState = &m_gameState;
    m_gameState.Restart();
}