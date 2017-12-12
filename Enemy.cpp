#include <SFML/Graphics.hpp>
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Plane.hpp"
#include <iostream>

Enemy::Enemy(sf::Vector2f l_size) : m_body(l_size), m_healthBar(sf::Vector2f(-500.f,-500.f)), m_damage(0){

    m_alive = true;
    // BODY
    m_body.setOutlineThickness(2.f);
    m_body.setOutlineColor(sf::Color::Black);
    // Fix random spawn as it is the same on every launch of the executable
    m_body.setPosition((float)(rand()%690 + 50), (float)(rand()%200));
    m_body.setFillColor(sf::Color::Red);

    m_healthBar.setPosition(m_body.getPosition());
}


void Enemy::Update(float timestep){

}

void Enemy::Render(sf::RenderWindow& l_window) {
    m_healthBar.Render(l_window);
    l_window.draw(m_body);
}

sf::Vector2f Enemy::GetSize(){
    return m_body.getSize();
}

sf::Vector2f Enemy::GetPosition() {
    return m_body.getPosition();
}

sf::FloatRect Enemy::GetGlobalBounds(){
    return m_body.getGlobalBounds();
}

void Enemy::TakeDamage(int l_damage){
    m_alive = m_healthBar.TakeDamage(l_damage);
}

bool Enemy::Collide(std::shared_ptr<GameObject> l_gameObject) {
    if (((l_gameObject->GetGlobalBounds().left > GetPosition().x) and (GetPosition().x + GetSize().x > l_gameObject->GetGlobalBounds().left) ) or \
        ((l_gameObject->GetGlobalBounds().left + l_gameObject->GetGlobalBounds().width > GetPosition().x) and ((GetPosition().x + GetSize().x) > l_gameObject->GetGlobalBounds().left + l_gameObject->GetGlobalBounds().width))) {
            if ((GetPosition().y < l_gameObject->GetGlobalBounds().top) and (GetPosition().y + GetSize().y > l_gameObject->GetGlobalBounds().top)){
                // Fix so that it takes the damage of the gameObjects
                // will all gameobjects be able to do damage ?
                TakeDamage(l_gameObject->GetDamage());
                return true;
            }
        }
    return false;
}

void Enemy::IncreaseDamage(int l_damage) {
    m_damage += l_damage;
}

void Enemy::DecreaseDamage(int l_damage){
    m_damage -= l_damage;
}

void Enemy::SetDamage(int l_damage){
    m_damage = l_damage;
}

int Enemy::GetDamage(){
    return m_damage;
}

bool Enemy::IsAlive(){
    return m_alive;
}

void Enemy::SetAlive(bool l_value) {
    m_alive = l_value;
}

int Enemy::Top() {
    return m_body.getPosition().y;
}

int Enemy::Bottom(){
    return m_body.getPosition().y + m_body.getSize().y;
}

int Enemy::Left(){
    return m_body.getPosition().x;
}

int Enemy::Right() {
    return m_body.getPosition().x + m_body.getSize().x;
}