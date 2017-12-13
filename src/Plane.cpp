#include <SFML/Graphics.hpp>
#include "Plane.hpp"
#include <iostream>
#include <chrono>
#include <cmath>

Plane::Plane(){
    m_width = 115.5f;
    m_height = 59.5f;
    m_planeVelocity = 200.f;
    m_velocity = {m_planeVelocity,m_planeVelocity};

    m_spawnTime = std::chrono::system_clock::now();

    // Start texture
    m_texture.loadFromFile("../assets/B-17.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setScale(.5f,.5f);
    m_sprite.setPosition(sf::Vector2f(400.f,300.f));
}

void Plane::Update(float timestep, sf::RenderWindow& l_window) {
    Move(timestep);
    Shoot(timestep,l_window);

}

void Plane::Move(float timestep){
    m_sprite.move(m_velocity.x*timestep,m_velocity.y*timestep);
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

void Plane::Shoot(float timestep,sf::RenderWindow& l_window){
    // we shoot bullets every .3 seconds
    // we have a timer on the last spawned bullet that we can check
    // if we do not have any bullets, then we use the timer present in this class
    // to keep the direction of the bullets in its class, we have a direction member
    // that is basically calculating the vector representing the direction of the rifle and then
    // we normalize it
    // NOTE : perhaps change the SQRT function with something more efficient ?
    auto ms = std::chrono::system_clock::now();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
        std::pair<sf::Vector2f,sf::Vector2f> l_position{getBulletSpawn()};
        // first bullet
        float magnitude_1{sqrt( pow( (l_position.first.x - sf::Mouse::getPosition(l_window).x),2) + pow( (l_position.first.y - sf::Mouse::getPosition(l_window).y),2))};
        float x_direction_1{(sf::Mouse::getPosition(l_window).x - l_position.first.x)/magnitude_1};
        float y_direction_1{(sf::Mouse::getPosition(l_window).y - l_position.first.y)/magnitude_1};

        float magnitude_2{sqrt( pow( (l_position.first.x - sf::Mouse::getPosition(l_window).x),2) + pow( (l_position.first.y - sf::Mouse::getPosition(l_window).y),2))};
        float x_direction_2{(sf::Mouse::getPosition(l_window).x - l_position.second.x)/magnitude_2};
        float y_direction_2{(sf::Mouse::getPosition(l_window).y - l_position.second.y)/magnitude_2};
        if ((!m_bullets.empty()) and (std::chrono::duration_cast<std::chrono::milliseconds>(ms - m_bullets[m_bullets.size()-1]->GetSpawnTime()).count() > 300)) {
            auto bullet_1 = std::make_shared<Bullet>(l_position.first, x_direction_1, y_direction_1);
            auto bullet_2 = std::make_shared<Bullet>(l_position.second, x_direction_2, y_direction_2);
            m_spawnTime = bullet_2->GetSpawnTime();
            m_bullets.push_back(bullet_1);
            m_bullets.push_back(bullet_2);
        } else if (std::chrono::duration_cast<std::chrono::milliseconds>(ms - m_spawnTime).count() > 300){
            auto bullet_1 = std::make_shared<Bullet>(l_position.first, x_direction_1, y_direction_1);
            auto bullet_2 = std::make_shared<Bullet>(l_position.second, x_direction_2, y_direction_2);
            m_bullets.push_back(bullet_1);
            m_bullets.push_back(bullet_2);
            m_spawnTime = bullet_1->GetSpawnTime();
        }
    }
    // This loop clears the bullets list if there are any buillets that 
    // have hit an enemy or out of window
    for (int i=0; i < m_bullets.size(); i++){
        m_bullets[i]->Update(timestep);
    }
    for (int i = m_bullets.size() - 1; i > -1; i--) {
        if (!m_bullets[i]->IsAlive()) {
            m_bullets.erase(m_bullets.begin() + i);
        }
    }
}

void Plane::Render(sf::RenderWindow& l_window){
    l_window.draw(m_sprite);
    l_window.draw(m_body);
    for (int i = 0; i < m_bullets.size(); i++){
        m_bullets[i]->Render(l_window);
    }
}

void Plane::HandleInput() {
    
}

float Plane::x() {
    return m_sprite.getPosition().x + m_width/2;
}

float Plane::y() {
    return m_sprite.getPosition().y + m_height/2;
}

float Plane::Left() {
    return x() - m_width/2.f;
}

float Plane::Right(){
    return x() + m_width/2.f;
}

float Plane::Top(){
    return y() - m_height/2.f;
}

float Plane::Bottom(){
    return y() + m_height/2.f;
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

std::pair<sf::Vector2f,sf::Vector2f> Plane::getBulletSpawn() {
    float x_1{Left() + 35.5f};
    float y_1{Top() + 10.f};

    float x_2{Left() + 81.f};
    float y_2{Top() + 10.f};
    return std::make_pair(sf::Vector2f(x_1,y_1),sf::Vector2f(x_2,y_2));
}

void Plane::Restart(){
    m_bullets.clear();
    m_body.setPosition(400.f,400.f);
}