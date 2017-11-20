#include <SFML/Graphics.hpp>
#include <iostream>
#include "Healthbar.hpp"

Healthbar::Healthbar(sf::Vector2f l_position) :  m_currentHealth(sf::Vector2f(50.f,7.f)), m_missingHealth(sf::Vector2f(0.f,0.f)), m_health(100) {
    
    // HEALTH
    m_currentHealth.setPosition(l_position.x, l_position.y - 7.f);
    m_currentHealth.setFillColor(sf::Color::Green);
}

void Healthbar::Update(float timestep){

}

void Healthbar::Render(sf::RenderWindow& l_window){
    l_window.draw(m_currentHealth);
}

void Healthbar::setPosition(sf::Vector2f l_position) {
    m_currentHealth.setPosition(sf::Vector2f(l_position.x, l_position.y-7));
}

void Healthbar::TakeDamage(int l_damage){
    m_currentHealth.setSize(sf::Vector2f((float)(l_damage/2),7.f))
}