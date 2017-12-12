
#pragma once
#include <SFML/Graphics.hpp>

class State {
public:
    void virtual Update(float timestep, sf::RenderWindow& l_window)=0;
    void virtual Render(sf::RenderWindow& l_window)=0;
    void virtual HandleInput()=0;
};