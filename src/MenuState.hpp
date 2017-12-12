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

        bool m_pressed;
        sf::Vector2i m_mousePosition;
        int m_buttonPressed[3];
    private:

        Button m_newGame;
        Button m_highScores;
        Button m_quitGame;
        sf::RectangleShape m_background;

};