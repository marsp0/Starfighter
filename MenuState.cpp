#include "SFML/Graphics.hpp"
#include "MenuState.hpp"

MenuState::MenuState() : m_newGame(sf::Vector2f(200.f,100.f), sf::Vector2f(100.f,120.f), sf::String("New Game")),
                        m_highScores(sf::Vector2f(200.f,100.f), sf::Vector2f(100.f,250.f), sf::String("High Scores")),
                        m_quitGame(sf::Vector2f(200.f,100.f), sf::Vector2f(100.f,380.f), sf::String("Quit Game"))
{

}

void MenuState::Update(float timestep, sf::RenderWindow& l_window) {

}

void MenuState::Render(sf::RenderWindow& l_window) {
    m_newGame.Render(l_window);
    m_highScores.Render(l_window);
    m_quitGame.Render(l_window);
}

void MenuState::HandleInput(){

}