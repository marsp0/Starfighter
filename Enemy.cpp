#include <SFML/Graphics.hpp>
#include "Enemy.hpp"
#include <iostream>

Enemy::Enemy(sf::Vector2f l_size) : m_body(l_size), m_healthBar(sf::Vector2f(-500.f,-500.f)){

    // BODY
    m_body.setOutlineThickness(2.f);
    m_body.setOutlineColor(sf::Color::Black);
    // Fix random spawn as it is the same on every launch of the executable
    m_body.setPosition((float)(rand()%690 + 50), (float)(rand()%100));
    m_body.setFillColor(sf::Color::Red);

    m_healthBar.setPosition(m_body.getPosition());
}


void Enemy::Update(float timestep){

}

void Enemy::Render(sf::RenderWindow& l_window) {
    m_healthBar.Render(l_window);
    l_window.draw(m_body);
}

sf::Vector2f Enemy::getPosition() {
    return m_body.getPosition();
}

sf::Vector2f Enemy::getSize() {
    return m_body.getSize();
}

void Enemy::TakeDamage(int l_damage){
    m_alive = m_healthBar.TakeDamage(l_damage);
}