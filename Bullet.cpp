#include <SFML/Graphics.hpp>
#include "Bullet.hpp"
#include <iostream>
#include <chrono>


Bullet::Bullet(sf::Vector2f l_position) : sf::CircleShape(6) {
    m_velocity = 450.f;
    sf::CircleShape::setPosition(l_position);
    sf::CircleShape::setOrigin(6,6);
    sf::CircleShape::setOutlineColor(sf::Color::Black);
    sf::CircleShape::setOutlineThickness(2.f);
    m_spawnTime = std::chrono::system_clock::now();
}

Bullet::~Bullet() {

}

bool Bullet::Update(float timestep) {
    if (sf::CircleShape::getPosition().y - m_velocity*timestep > 0){
        sf::CircleShape::move(0, -m_velocity*timestep);
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