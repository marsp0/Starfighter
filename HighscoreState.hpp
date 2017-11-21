#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"

class HighscoreState : public State { 
    public:
        HighscoreState();

        void Render(sf::RenderWindow& l_window);
        void Update(float timestep, sf::RenderWindow& l_window);
        void HandleInput();
        sf::String GetMessage();
        std::vector<std::string> m_highScores;
        
    private:
        sf::Text m_text;
        sf::Font m_font;
        sf::RectangleShape m_background;
        int m_maxSize;
};