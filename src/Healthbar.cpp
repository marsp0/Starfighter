#include <SFML/Graphics.hpp>
#include <iostream>
#include "Healthbar.hpp"


Healthbar::Healthbar(sf::Vector2f l_position) :  m_currentHealth(sf::Vector2f(HP_WIDTH, HP_HEIGHT)), m_missingHealth(sf::Vector2f(0.f,HP_HEIGHT)), m_health(100) {
    
    // HEALTH
    m_currentHealth.setPosition(l_position.x, l_position.y - 7.f);
    m_currentHealth.setFillColor(sf::Color::Green);

    m_missingHealth.setFillColor(sf::Color::Red);

}

void Healthbar::Update(float timestep){

}

void Healthbar::Render(sf::RenderWindow& l_window){
    l_window.draw(m_currentHealth);
    l_window.draw(m_missingHealth);
}

void Healthbar::setPosition(sf::Vector2f l_position) {
    m_currentHealth.setPosition(sf::Vector2f(l_position.x, l_position.y-7));
}

bool Healthbar::TakeDamage(int l_damage){
    if (m_health - l_damage <= 0) {
        return false;
    } else {
        m_currentHealth.setSize(sf::Vector2f((float)((m_health-l_damage))*HP_WIDTH/100,7.f));
        m_health = m_health-l_damage;


        m_missingHealth.setPosition(sf::Vector2f(m_currentHealth.getPosition().x+m_currentHealth.getSize().x, m_currentHealth.getPosition().y));
        m_missingHealth.setSize(sf::Vector2f(HP_WIDTH - m_currentHealth.getSize().x, HP_HEIGHT));


        return true;
    }
}