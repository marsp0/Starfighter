#include <SFML/Graphics.hpp>
#include "Bullet.hpp"
#include <iostream>
#include <chrono>


Bullet::Bullet(sf::Vector2f l_position, float x_direction, float y_direction) : m_body(6), m_direction(x_direction,y_direction) {

    m_alive = true;
    m_velocity = 450.f;
    m_body.setPosition(l_position);
    m_body.setOrigin(6,6);
    m_body.setOutlineColor(sf::Color::Black);
    m_body.setOutlineThickness(2.f);
    m_spawnTime = std::chrono::system_clock::now();
    m_damage = 30;
}

Bullet::~Bullet() {

}

bool Bullet::Update(float timestep) {
    if ((m_body.getPosition().y - m_velocity*timestep > 0) and (m_body.getPosition().x - m_velocity*timestep > 0)){
        m_body.move(m_direction.x*m_velocity*timestep, m_direction.y*m_velocity*timestep);
        return true;
    } else {
        return false;
    }
}

void Bullet::Render(sf::RenderWindow& l_window) {
    l_window.draw(m_body);
}

sf::Vector2f Bullet::GetPosition(){
    return m_body.getPosition();
}

sf::FloatRect Bullet::GetGlobalBounds() {
    return m_body.getGlobalBounds();
}

int Bullet::Top(){
    return m_body.getPosition().y + m_body.getOrigin().y - m_body.getRadius();
}

int Bullet::Bottom() {
    return m_body.getPosition().y + m_body.getOrigin().y + m_body.getRadius();
}

int Bullet::Left(){
    
    return m_body.getPosition().x + m_body.getOrigin().x - m_body.getRadius();
}

int Bullet::Right() {
    return m_body.getPosition().x + m_body.getOrigin().x + m_body.getRadius();
}

std::chrono::time_point<std::chrono::system_clock> Bullet::GetSpawnTime() {
    return m_spawnTime;
}

void Bullet::IncreaseDamage(int l_damage) {
    m_damage += l_damage;
}

void Bullet::DecreaseDamage(int l_damage){
    m_damage -= l_damage;
}

void Bullet::SetDamage(int l_damage){
    m_damage = l_damage;
}

int Bullet::GetDamage(){
    return m_damage;
}

bool Bullet::Collide(std::shared_ptr<GameObject> l_gameObject) {
}

bool Bullet::IsAlive() {
    return m_alive;
}

void Bullet::SetAlive(bool l_value) {
    m_alive = l_value;
}