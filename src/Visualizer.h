#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TimedObject.h"
#include "MyMusicPlayer.h"

class Visualizer {
public:
    Visualizer(sf::RenderWindow& window);
    void draw();
    void loadMusic(std::string path);
    void stopMusic();
    void setSamples(const sf::Int16 *samples, size_t sampleCount);
    void onEvent(sf::Event& e);
protected:
    double m_currentProfileWidth = 0.0;
public:
    double getM_currentProfileWidth() const;

protected:
    size_t m_currentSample = 0;
    sf::RenderWindow* m_window;
    MyMusicPlayer m_music;
    std::vector<sf::Int16> m_samples;
    std::vector<std::tuple<std::unique_ptr<sf::RectangleShape>, size_t>> m_drawObjects;
};