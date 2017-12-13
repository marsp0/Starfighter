#include <SFML/Graphics.hpp>
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Plane.hpp"
#include <iostream>

Enemy::Enemy(sf::Vector2f l_size) : m_healthBar(sf::Vector2f(-500.f,-500.f)), m_damage(0){

    m_alive = true;
    // BODY

    m_scale = .29f;

    m_texture.loadFromFile("../assets/enemyShip.png");
    m_sprite.setTexture(m_texture);
    m_sprite.scale(m_scale,m_scale);
    m_sprite.setPosition((float)(rand()%690 + 50), (float)(rand()%200));
    m_width = 114.f;
    m_height = 201.f;

    m_healthBar.setPosition(m_sprite.getPosition());
    m_healthBar.setSize(sf::Vector2f(114.4 * m_scale, 7.f));
}


void Enemy::Update(float timestep){

}

void Enemy::Render(sf::RenderWindow& l_window) {
    l_window.draw(m_sprite);
    m_healthBar.Render(l_window);
}

sf::Vector2f Enemy::GetSize(){
    return sf::Vector2f(m_sprite.getTextureRect().width * m_scale, m_sprite.getTextureRect().height * m_scale);
}

sf::Vector2f Enemy::GetPosition() {
    return m_sprite.getPosition();
}

sf::FloatRect Enemy::GetGlobalBounds(){
    return m_sprite.getGlobalBounds();
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
    return m_sprite.getPosition().y;
}

int Enemy::Bottom(){
    return m_sprite.getPosition().y + GetSize().y;
}

int Enemy::Left(){
    return m_sprite.getPosition().x;
}

int Enemy::Right() {
    return m_sprite.getPosition().x + GetSize().x;
}