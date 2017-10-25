#include <SFML/Graphics.hpp>
#include "Plane.hpp"
#include <iostream>

Plane::Plane() : sf::CircleShape(40,3){
    m_planeVelocity = 200.f;
    m_velocity = {m_planeVelocity,m_planeVelocity};
    sf::CircleShape::setFillColor(sf::Color(48, 48, 48));
    sf::CircleShape::setOrigin(40,40);
    sf::CircleShape::setOutlineColor(sf::Color::Black);
    sf::CircleShape::setOutlineThickness(2.0f);

}

Plane::~Plane() {

}

void Plane::Update(float timestep) {
    Move(timestep);
    Shoot(timestep);
}

void Plane::Move(float timestep){
    sf::CircleShape::move(m_velocity.x*timestep,m_velocity.y*timestep);
    if ((Right() < 800) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))){        
        m_velocity.x = m_planeVelocity;
        if ((Left() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))){
            m_velocity.x = 0;
        } else if ((Top() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))) {
            m_velocity.y = -m_planeVelocity;
        } else if ((Bottom() < 600) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))){
            m_velocity.y = m_planeVelocity;
        } else {
            m_velocity.y = 0;
        }
    } else if ((Left() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))) {
        m_velocity.x = -m_planeVelocity;
        if ((Right() < 800) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))){
            m_velocity.x = 0;
        } else if ((Top() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))) {
            m_velocity.y = -m_planeVelocity;
        } else if ((Bottom() < 600) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))){
            m_velocity.y = m_planeVelocity;
        } else {
            m_velocity.y = 0;
        }
    } else if ((Top() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))){
        m_velocity.y = -m_planeVelocity;
        if ((Bottom() < 600) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))){
            m_velocity.y = 0;
        } else if ((Right() < 800) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))){
            m_velocity.x = m_planeVelocity;
        } else if( (Left() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))) {
            m_velocity.x = -m_planeVelocity;
        } else {
            m_velocity.x = 0;
        }
    } else if ((Bottom() < 600) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))){
        m_velocity.y = m_planeVelocity;
        if ((Top() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))){
            m_velocity.y = 0;
        } else if ((Right() < 800) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))){
            m_velocity.x = m_planeVelocity;
        } else if( (Left() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))) {
            m_velocity.x = -m_planeVelocity;
        } else {
            m_velocity.x = 0;
        }
    } else {
        m_velocity.x = 0.f;
        m_velocity.y = 0.f;
    }
}

void Plane::Shoot(float timestep){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
        Bullet bullet(sf::CircleShape::getPosition());
        m_bullets.push_back(bullet);
    }
    for (int i=0; i < m_bullets.size(); i++){
        bool temp;
        temp = m_bullets[i].Update(timestep);
        if (!temp){
            m_bullets.erase(m_bullets.begin()+i);
        }
    }
}

void Plane::Render(sf::RenderWindow& l_window){
    l_window.draw(*this);
    for (int i = 0; i < m_bullets.size(); i++){
        l_window.draw(m_bullets[i]);
    }
}

void Plane::HandleInput() {
    
}

float Plane::x() {
    return sf::CircleShape::getPosition().x;
}

float Plane::y() {
    return sf::CircleShape::getPosition().y;
}

float Plane::Left() {
    return sf::CircleShape::getPosition().x-sf::CircleShape::getRadius();
}

float Plane::Right(){
    return sf::CircleShape::getPosition().x + sf::CircleShape::getRadius();
}

float Plane::Top(){
    return sf::CircleShape::getPosition().y - sf::CircleShape::getRadius();
}

float Plane::Bottom(){
    return sf::CircleShape::getPosition().y + sf::CircleShape::getRadius();
}