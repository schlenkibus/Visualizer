#include <iostream>
#include <SFML/Graphics.hpp>
#include "Visualizer.h"


struct Application {

    sf::RenderWindow window;

    Visualizer visuals;

    Application() : window{sf::VideoMode(1920, 1080), "", sf::Style::Fullscreen}, visuals(window) {}

    sf::Color getColorFromWidth(double value) {
        const auto t1 = value * 255;
        auto t2 = t1 / SHRT_MAX;
        t2 -= 20;
        return sf::Color(static_cast<sf::Uint8>(187),
                         static_cast<sf::Uint8>(t2 + 40),
                         static_cast<sf::Uint8>(t2));
    }

    int run(char* path) {
        window.setVerticalSyncEnabled(true);
        sf::Event e{};
        visuals.loadMusic(path);
        while(window.isOpen()) {
            while(window.pollEvent(e)) {
                if(e.type == sf::Event::Closed) {
                    window.close();
                    visuals.stopMusic();
                    return 0;
                }
                else {
                    visuals.onEvent(e);
                }
            }
            window.clear(getColorFromWidth(visuals.getM_currentProfileWidth()));
            visuals.draw();
            window.display();
        }
        return 0;
    }


} static theApp;


int main(int argc, char** argv) {
    if(argc < 2) {
        std::cerr << "[ERROR] Filename missing! use: " << argv[0] << " <filename>";
        return 1;
    }
    return theApp.run(argv[1]);
}