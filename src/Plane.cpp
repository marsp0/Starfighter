#include <SFML/Graphics.hpp>
#include "Plane.hpp"
#include <iostream>
#include <chrono>
#include <cmath>

Plane::Plane() : m_body(40,3), m_rifle(sf::Vector2f(14.f,45.f)){
    m_planeVelocity = 200.f;
    m_velocity = {m_planeVelocity,m_planeVelocity};
    m_body.setFillColor(sf::Color(48, 48, 48));
    m_body.setOrigin(40,40);
    m_body.setOutlineColor(sf::Color::Black);
    m_body.setOutlineThickness(2.0f);
    m_body.setPosition(sf::Vector2f(400.f,300.f));
    m_spawnTime = std::chrono::system_clock::now();
    m_sideDistance = std::sqrt(std::pow(m_body.getPoint(0).x - m_body.getPoint(1).x, 2) + std::pow(m_body.getPoint(0).y - m_body.getPoint(1).y, 2));

    // RIFLE

    m_rifle.setOrigin(sf::Vector2f(7.f,45.f));
    m_rifle.setFillColor(sf::Color::White);
    m_rifle.setOutlineColor(sf::Color::Black);
    m_rifle.setOutlineThickness(2.f);
    m_rifle.setPosition(m_body.getPosition());

    // Start texture
    m_texture.loadFromFile("assets/B-17.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(50.f,50.f);
    m_sprite.setScale(.6f,.6f);
    std::cout << m_sprite.getPosition().x << std::endl;

}

void Plane::Update(float timestep, sf::RenderWindow& l_window) {
    Move(timestep);
    
    sf::Vector2i l_mousePosition{sf::Mouse::getPosition(l_window)}; 
    m_rifle.setRotation(getRotationAngle(l_mousePosition));
    Shoot(timestep);

}

void Plane::Move(float timestep){
    // we move the plane and the rifle accordingly based on the buttons pressed
    m_body.move(m_velocity.x*timestep,m_velocity.y*timestep);
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
    // we shoot bullets every .3 seconds
    // we have a timer on the last spawned bullet that we can check
    // if we do not have any bullets, then we use the timer present in this class
    // to keep the direction of the bullets in its class, we have a direction member
    // that is basically calculating the vector representing the direction of the rifle and then
    // we normalize it
    // NOTE : perhaps change the SQRT function with something more efficient ?
    auto ms = std::chrono::system_clock::now();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
        sf::Vector2f l_position{getBulletSpawn()};
        float magnitude{sqrt( pow( (l_position.x - m_rifle.getPosition().x),2) + pow( (l_position.y - m_rifle.getPosition().y),2))};
        float x_direction{(l_position.x - m_rifle.getPosition().x)/magnitude};
        float y_direction{(l_position.y - m_rifle.getPosition().y)/magnitude};
        if ((!m_bullets.empty()) and (std::chrono::duration_cast<std::chrono::milliseconds>(ms - m_bullets[m_bullets.size()-1]->GetSpawnTime()).count() > 300)) {
            auto bullet = std::make_shared<Bullet>(l_position, x_direction, y_direction);
            m_spawnTime = bullet->GetSpawnTime();
            m_bullets.push_back(bullet);
        } else if (std::chrono::duration_cast<std::chrono::milliseconds>(ms - m_spawnTime).count() > 300){
            auto bullet = std::make_shared<Bullet>(l_position, x_direction, y_direction);
            m_bullets.push_back(bullet);
            m_spawnTime = bullet->GetSpawnTime();
        }
    }
    // This loop clears the bullets list if there are any buillets that 
    // have hit an enemy or out of window
    for (int i=0; i < m_bullets.size(); i++){
        bool temp;
        temp = m_bullets[i]->Update(timestep);
        if (!temp){
            m_bullets.erase(m_bullets.begin()+i);
        }
    }
}

void Plane::Render(sf::RenderWindow& l_window){
    l_window.draw(m_sprite);
    l_window.draw(m_body);
    l_window.draw(m_rifle);
    for (int i = 0; i < m_bullets.size(); i++){
        m_bullets[i]->Render(l_window);
    }
}

void Plane::HandleInput() {
    
}

float Plane::x() {
    return m_body.getPosition().x;
}

float Plane::y() {
    return m_body.getPosition().y;
}

float Plane::Left() {
    return m_body.getPosition().x - m_sideDistance/2;
}

float Plane::Right(){
    return m_body.getPosition().x + m_sideDistance/2;
}

float Plane::Top(){
    return m_body.getPosition().y - m_body.getRadius();
}

float Plane::Bottom(){
    return m_body.getPosition().y + 0.5 * m_body.getRadius();
}

float Plane::getRotationAngle(sf::Vector2i l_mousePosition){
    // This function gets the rotation angle that helps us track the mouse position with the gun
    // Explanation : 
    //                  RP - angle at mouse position
    //   |\      |      K - Axis of rotation of our gun
    //   | \     |      RK = RP (K || P) - Angle that we want to rotate our gun
    //   |  \ R  |      P = My - Gy
    // P |   \   |  K   Q = Gx - Mx
    //   |    \  |      Solution : RP = RK = atan(Q/P)
    //   |     \ |      We could try asin and acos (and I did), but I believe that because of the RANGE
    //   |______\|      of these functions we are not getting the correct result. Might be wrong though
    //      Q
    // 
    // 
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
    m_body.setPosition(400.f,400.f);
}