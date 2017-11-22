#include <SFML/Graphics.hpp>
#include "Scoreboard.hpp"
#include <iostream>

Scoreboard::Scoreboard() : m_lives(3), m_score(0) {

    m_font.loadFromFile("zorque.ttf");
    m_text.setFont(m_font);
    m_text.setString(GetMessage());
    m_text.setColor(sf::Color::White);
    m_text.setPosition(10.f,10.f);
    m_text.setCharacterSize(20);
}

void Scoreboard::Render(sf::RenderWindow& l_window){
    l_window.draw(m_text);
}

void Scoreboard::Update(float timestep){
    m_text.setString(GetMessage());
}

std::string Scoreboard::GetMessage(){
    return "Lives : " + std::to_string(m_lives) +  "\nScore : " + std::to_string(m_score);
}

void Scoreboard::AddLive(){
    m_lives += 1;
}

void Scoreboard::RemoveLive() {
    m_lives -= 1;
}

void Scoreboard::AddScore(int l_score) {
    m_score += l_score;
}

void Scoreboard::RemoveScore(int l_score) {
    m_score -= l_score;
}

void Scoreboard::Restart(){
    m_score = 0;
    m_lives = 3;
}