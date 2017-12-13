#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class GameObject {
    public:
        sf::Vector2f virtual GetPosition()=0;
        sf::FloatRect virtual GetGlobalBounds()=0;

        int virtual Top()=0;
        int virtual Bottom()=0;
        int virtual Left()=0;
        int virtual Right()=0;
        void virtual Render(sf::RenderWindow& l_window)=0;
        bool virtual Collide(std::shared_ptr<GameObject> l_gameObject)=0;
        void virtual SetAlive(bool l_value)=0;
        bool virtual IsAlive()=0;
        void virtual IncreaseDamage(int l_damage)=0;
        void virtual DecreaseDamage(int l_damage)=0;
        void virtual SetDamage(int l_damage)=0;
        int virtual GetDamage()=0;
        void virtual TakeDamage(int l_damage)=0;
};