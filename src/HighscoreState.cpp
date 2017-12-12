#include <SFML/Graphics.hpp>
#include "HighscoreState.hpp"
#include <fstream>
#include <iostream>

HighscoreState::HighscoreState() : m_maxSize(0){
    // std::fstream l_scores;
    // l_scores.open("scores.txt");
    // std::string str;
    // while(getline(l_scores, str))
    // {
    //     m_highScores.push_back(str + "\n");
    // }
    // l_scores.close();
    
    // TODO : Load from stream or pass via constructor
    m_font.loadFromFile("zorque.ttf");
    m_text.setFont(m_font);
    m_text.setString(GetMessage());
    m_text.setPosition(0.f,0.f);
    m_text.setPosition((800 - m_text.getLocalBounds().width)/2, (600 - m_text.getLocalBounds().height)/2);
}

void HighscoreState::Render(sf::RenderWindow& l_window) {
    l_window.draw(m_text);
}

void HighscoreState::Update(float timestep, sf::RenderWindow& l_window) {

}

void HighscoreState::HandleInput() {

}

sf::String HighscoreState::GetMessage() {
    sf::String result;
    for (int i=0; i < m_highScores.size(); i++) {
        result += m_highScores[i];
        if (m_highScores[i].size() > m_maxSize) {
            m_maxSize = m_highScores[i].size();
        }
    }
    return result;
}