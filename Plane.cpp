#include <SFML/Graphics.hpp>
#include "Plane.hpp"
#include <iostream>
#include <chrono>
#include <cmath>

Plane::Plane() : sf::CircleShape(40,3), m_rifle(sf::Vector2f(14.f,45.f)){
    m_planeVelocity = 200.f;
    m_velocity = {m_planeVelocity,m_planeVelocity};
    sf::CircleShape::setPosition(sf::Vector2f(400.f,300.f));
    sf::CircleShape::setFillColor(sf::Color(48, 48, 48));
    sf::CircleShape::setOrigin(40,40);
    sf::CircleShape::setOutlineColor(sf::Color::Black);
    sf::CircleShape::setOutlineThickness(2.0f);
    m_spawnTime = std::chrono::system_clock::now();
    m_sideDistance = std::sqrt(std::pow(sf::CircleShape::getPoint(0).x - sf::CircleShape::getPoint(1).x, 2) + std::pow(sf::CircleShape::getPoint(0).y - sf::CircleShape::getPoint(1).y, 2));

    // RIFLE

    m_rifle.setOrigin(sf::Vector2f(7.f,45.f));
    m_rifle.setFillColor(sf::Color::White);
    m_rifle.setOutlineColor(sf::Color::Black);
    m_rifle.setOutlineThickness(2.f);
    m_rifle.setPosition(sf::CircleShape::getPosition());

}

Plane::~Plane() {

}

void Plane::Update(float timestep, sf::RenderWindow& l_window) {
    Move(timestep);
    
    sf::Vector2i l_mousePosition{sf::Mouse::getPosition(l_window)}; 
    m_rifle.setRotation(getRotationAngle(l_mousePosition));
    Shoot(timestep);

}

void Plane::Move(float timestep){
    sf::CircleShape::move(m_velocity.x*timestep,m_velocity.y*timestep);
    m_rifle.move(m_velocity.x*timestep,m_velocity.y*timestep);
    if ((Right() < 800) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))){        
        m_velocity.x = m_planeVelocity;
        if ((Left() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))){
            m_velocity.x = 0;
        } else if ((Top() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))) {
            m_velocity.y = -m_planeVelocity;
        } else if ((Bottom() < 600) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))){
            m_velocity.y = m_planeVelocity;
        } else {
            m_velocity.y = 0;
        }
    } else if ((Left() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))) {
        m_velocity.x = -m_planeVelocity;
        if ((Right() < 800) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))){
            m_velocity.x = 0;
        } else if ((Top() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))) {
            m_velocity.y = -m_planeVelocity;
        } else if ((Bottom() < 600) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))){
            m_velocity.y = m_planeVelocity;
        } else {
            m_velocity.y = 0;
        }
    } else if ((Top() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))){
        m_velocity.y = -m_planeVelocity;
        if ((Bottom() < 600) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))){
            m_velocity.y = 0;
        } else if ((Right() < 800) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))){
            m_velocity.x = m_planeVelocity;
        } else if( (Left() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))) {
            m_velocity.x = -m_planeVelocity;
        } else {
            m_velocity.x = 0;
        }
    } else if ((Bottom() < 600) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))){
        m_velocity.y = m_planeVelocity;
        if ((Top() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))){
            m_velocity.y = 0;
        } else if ((Right() < 800) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))){
            m_velocity.x = m_planeVelocity;
        } else if( (Left() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))) {
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
    auto ms = std::chrono::system_clock::now();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
        sf::Vector2f l_position{getBulletSpawn()};
        float magnitude{sqrt( pow( (l_position.x - m_rifle.getPosition().x),2) + pow( (l_position.y - m_rifle.getPosition().y),2))};
        float x_direction{(l_position.x - m_rifle.getPosition().x)/magnitude};
        float y_direction{(l_position.y - m_rifle.getPosition().y)/magnitude};
        if ((!m_bullets.empty()) and (std::chrono::duration_cast<std::chrono::milliseconds>(ms - m_bullets[m_bullets.size()-1].GetSpawnTime()).count() > 300)) {
            Bullet bullet(l_position, x_direction, y_direction);
            m_spawnTime = bullet.GetSpawnTime();
            m_bullets.push_back(bullet);
        } else if (std::chrono::duration_cast<std::chrono::milliseconds>(ms - m_spawnTime).count() > 300){
            Bullet bullet(l_position, x_direction, y_direction);
            m_bullets.push_back(bullet);
            m_spawnTime = bullet.GetSpawnTime();
        }
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
    l_window.draw(m_rifle);

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
    return sf::CircleShape::getPosition().x - m_sideDistance/2;
}

float Plane::Right(){
    return sf::CircleShape::getPosition().x + m_sideDistance/2;
}

float Plane::Top(){
    return sf::CircleShape::getPosition().y - sf::CircleShape::getRadius();
}

float Plane::Bottom(){
    return sf::CircleShape::getPosition().y + 0.5 * sf::CircleShape::getRadius();
}

float Plane::getRotationAngle(sf::Vector2i l_mousePosition){
    sf::Vector2f l_mousePos{l_mousePosition};
    return atan2(m_rifle.getPosition().y - l_mousePos.y, m_rifle.getPosition().x - l_mousePos.x)*180.f/3.1428 - 90;
}

sf::Vector2f Plane::getBulletSpawn() {
    float x {(float)(m_rifle.getPosition().x + m_rifle.getSize().y * sin(m_rifle.getRotation()*3.1428/180))};
    float y {(float)(m_rifle.getPosition().y - m_rifle.getSize().y * sin((90-m_rifle.getRotation())*3.1428/180))};
    return sf::Vector2f(x , y);
}

void Plane::Restart(){
    m_bullets.clear();
    m_rifle.setPosition(400.f, 400.f);
    sf::CircleShape::setPosition(400.f,400.f);
}