#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <thread>
#include <numeric>
#include "Visualizer.h"

Visualizer::Visualizer(sf::RenderWindow& window) : m_window(&window), m_music(*this) {
    for(int i = 0; i < 960; i++) {
        m_drawObjects.emplace_back(std::make_tuple(std::make_unique<sf::RectangleShape>(), 0));
        auto& obj = m_drawObjects.back();
        auto& draw = std::get<0>(obj);
        draw->setPosition(i*2, 0);
        draw->setSize(sf::Vector2f(2,20));
    }
}

sf::Color toColor(sf::Int16 sample) {
    const auto t1 = sample * 255;
    int t2 = t1 / SHRT_MAX;
    return sf::Color(static_cast<sf::Uint8>(t2),
                    static_cast<sf::Uint8>(255 - t2),
                    static_cast<sf::Uint8>(255 - t2 / 2));
}


void Visualizer::draw() {
    static sf::Clock redrawNeeded;
    for(auto& v: m_drawObjects) {

        if(m_samples.size() > 0)
            m_currentProfileWidth = std::accumulate( &m_samples[m_currentSample], &m_samples[m_currentSample + 960], 0.0)/m_samples.size();

        auto samplesPerSecond = m_music.getSampleRate();
        if(redrawNeeded.getElapsedTime().asSeconds() > 2 / samplesPerSecond) {
            if(m_currentSample < m_samples.size()) {
                redrawNeeded.restart();
                auto& draw = std::get<0>(v);
                auto& index = std::get<1>(v);
                auto currentValue = m_samples[m_currentSample + index];
                draw->setFillColor(toColor(currentValue));
                const auto t = currentValue * 1080;
                draw->setSize(sf::Vector2f(2, t / SHRT_MAX * 2));
                m_currentSample++;
            } else {
                m_currentSample = 0;
            }
        }

        m_window->draw(*std::get<0>(v).get());
    }


    std::cout << m_currentProfileWidth << '\n';
}

void Visualizer::loadMusic(std::string path) {
    m_music.openFromFile(path);
    m_music.setAttenuation(0.67);
    m_music.play();
}

void Visualizer::stopMusic() {
    m_music.stop();
}

void Visualizer::setSamples(const sf::Int16 *samples, size_t sampleCount) {
    m_samples.clear();
    m_samples.insert(m_samples.end(), &samples[0], &samples[sampleCount]);

    int index = 0;
    for(auto& drawObj: m_drawObjects) {
        auto& indexObj = std::get<1>(drawObj);
        indexObj = index;
        index++;
    }
}

void Visualizer::onEvent(sf::Event& e) {
    if(e.type == sf::Event::KeyReleased) {
        auto inSeconds = m_music.getPlayingOffset();
        switch(e.key.code) {
            case sf::Keyboard::Key::Right:
                m_music.setPlayingOffset(inSeconds);
                break;
            case sf::Keyboard::Key::Left:
                m_music.setPlayingOffset(inSeconds - sf::seconds(2));
                break;
            default:
                exit(2);
        }
    }
}

double Visualizer::getM_currentProfileWidth() const {
    return m_currentProfileWidth;
}
