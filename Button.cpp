#include <SFML/Graphics.hpp>
#include "Button.hpp"

Button::Button(sf::Vector2f l_size, sf::Vector2f l_position, sf::String l_title) : m_background(l_size) {
    m_font.loadFromFile("zorque.ttf");
    m_text.setFont(m_font);
    m_text.setString(l_title);
    m_text.setCharacterSize(30);
    m_text.setPosition(l_position.x+(l_size.x - m_text.getLocalBounds().width)/2 , l_position.y + l_size.y/2 - m_text.getLocalBounds().height);
    m_background.setOutlineColor(sf::Color::Black);
    m_background.setOutlineThickness(2.f);
    m_background.setFillColor(sf::Color::Green);
    m_background.setPosition(l_position);
}

void Button::Update(float timestep){
}

void Button::Render(sf::RenderWindow& l_window){
    l_window.draw(m_background);
    l_window.draw(m_text);
}