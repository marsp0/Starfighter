#include <SFML/Graphics.hpp>
#include "Bullet.hpp"
#include <iostream>
#include <chrono>


Bullet::Bullet(sf::Vector2f l_position, float x_direction, float y_direction) : sf::CircleShape(6), m_direction(x_direction,y_direction) {
    m_velocity = 450.f;
    sf::CircleShape::setPosition(l_position);
    sf::CircleShape::setOrigin(6,6);
    sf::CircleShape::setOutlineColor(sf::Color::Black);
    sf::CircleShape::setOutlineThickness(2.f);
    m_spawnTime = std::chrono::system_clock::now();
    m_damage = 30;
}

Bullet::~Bullet() {

}

bool Bullet::Update(float timestep) {
    if ((sf::CircleShape::getPosition().y - m_velocity*timestep > 0) and (sf::CircleShape::getPosition().x - m_velocity*timestep > 0)){
        sf::CircleShape::move(m_direction.x*m_velocity*timestep, m_direction.y*m_velocity*timestep);
        return true;
    } else {
        return false;
    }
}

sf::Vector2f Bullet::getPosition(){
    return sf::CircleShape::getPosition();
}

float Bullet::Top(){
    return sf::CircleShape::getOrigin().y - sf::CircleShape::getRadius();
}

float Bullet::Bottom() {
    return sf::CircleShape::getOrigin().y + sf::CircleShape::getRadius();
}

float Bullet::Left(){
    return sf::CircleShape::getOrigin().x - sf::CircleShape::getRadius();
}

float Bullet::Right() {
    return sf::CircleShape::getOrigin().x + sf::CircleShape::getRadius();
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