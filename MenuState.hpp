#pragma once

#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "State.hpp"

class MenuState : public State{
    public:
        MenuState();

        void Update(float timestep, sf::RenderWindow& l_window);
        void Render(sf::RenderWindow& l_window);
        void HandleInput();
    private:

        Button m_newGame;
        Button m_highScores;
        Button m_quitGame;
};