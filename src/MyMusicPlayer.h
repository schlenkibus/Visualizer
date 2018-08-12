#pragma once
#include <SFML/Audio.hpp>


class Visualizer;

class MyMusicPlayer : public sf::Music {
public:
    MyMusicPlayer(Visualizer& parent);
protected:
    virtual bool onGetData(Chunk& data);
    Visualizer& m_parent;
};