#include "SFML/Graphics.hpp"
#include "MenuState.hpp"
#include <iostream>

MenuState::MenuState() : m_newGame(sf::Vector2f(200.f,100.f), sf::Vector2f(300.f,120.f), sf::String("New Game")),
                        m_highScores(sf::Vector2f(200.f,100.f), sf::Vector2f(300.f,250.f), sf::String("High Scores")),
                        m_quitGame(sf::Vector2f(200.f,100.f), sf::Vector2f(300.f,380.f), sf::String("Quit Game"))
{
    m_background.setPosition(sf::Vector2f(270.f,90.f));
    m_background.setFillColor(sf::Color::Blue);
    m_background.setOutlineColor(sf::Color::Black);
    m_background.setOutlineThickness(2.f);
    m_background.setSize(sf::Vector2f(260.f,420.f));
    for (int i = 0; i < 3; i++) {
        m_buttonPressed[i] = false;
    }
}

void MenuState::Update(float timestep, sf::RenderWindow& l_window) {
    int temp{0};
    if (m_pressed) {
        if (m_newGame.GetGlobalBounds().contains(m_mousePosition.x, m_mousePosition.y)) {
            m_buttonPressed[0] = true;
            temp = 0;
        } else if (m_highScores.GetGlobalBounds().contains(m_mousePosition.x, m_mousePosition.y)) {
            m_buttonPressed[1] = true;
            temp = 1;
        } else if (m_quitGame.GetGlobalBounds().contains(m_mousePosition.x, m_mousePosition.y)) {
            m_buttonPressed[2] = true;
            temp = 2;
        }
        m_pressed = false;
    }
}

void MenuState::Render(sf::RenderWindow& l_window) {
    l_window.draw(m_background);
    m_newGame.Render(l_window);
    m_highScores.Render(l_window);
    m_quitGame.Render(l_window);
}

void MenuState::HandleInput(){

}