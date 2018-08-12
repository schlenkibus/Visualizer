#include "MyMusicPlayer.h"
#include "Visualizer.h"

MyMusicPlayer::MyMusicPlayer(Visualizer &parent) : m_parent(parent) {

}

bool MyMusicPlayer::onGetData(sf::SoundStream::Chunk& data)
{
    bool result = sf::Music::onGetData(data);
    m_parent.setSamples(data.samples, data.sampleCount);
    return result;
}