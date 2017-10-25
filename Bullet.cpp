#include <SFML/Graphics.hpp>
#include "Bullet.hpp"
#include <iostream>

Bullet::Bullet(sf::Vector2f l_position) : sf::CircleShape(6) {
    m_velocity = 450.f;
    sf::CircleShape::setPosition(l_position);
    sf::CircleShape::setOrigin(6,6);
    sf::CircleShape::setOutlineColor(sf::Color::Black);
    sf::CircleShape::setOutlineThickness(2.f);
    
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

void Bullet::getPosition(){

}

float Bullet::Top(){

}

float Bullet::Bottom() {

}

float Bullet::Left(){

}

float Bullet::Right() {

}