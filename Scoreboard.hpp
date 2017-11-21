#pragma once

#include <SFML/Graphics.hpp>

class Scoreboard {
    public:
        Scoreboard();

        void Update(float timestep);
        void Render(sf::RenderWindow& l_window);

        std::string GetMessage();

        void AddLive();
        void RemoveLive();

        void AddScore(int l_score);
        void RemoveScore(int l_score);

    private:
        
        int m_lives;
        int m_score;

        sf::Text m_text;
        sf::Font m_font;

        // buffs

};