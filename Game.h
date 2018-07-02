//
// Created by William Webster on 28/06/2018.
//

#ifndef SK_IVER_GAME_H
#define SK_IVER_GAME_H


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Ring.h"
#include "Background.h"
#include "Diver.h"
#include "HandleEvents.h"

class Game {
public:
    void setUp();
    void update();

private:
    // setUp() variables:
    sf::Vector2u screenDimensions; // a 3:2 resolution, for 16:9 = (1920, 1080)
    std::string titleString;
    sf::RenderWindow window;
    sf::SoundBuffer musicBuffer;
    sf::Sound music;
    sf::Font font;
    sf::Color titleColour, scoreColour;
    sf::Text title, score;
    sf::Vector2f titlePosition, scorePosition;
    int textAlpha = 256, playerScore = 0;
    std::vector<Ring> rings;
    sf::View backgroundView, playerView;
    bool quitGame = false;

    // other variables:
//    Diver player = Diver(window.getSize());
//    Background background = Background(window.getSize());
    sf::Clock clock;
    float frameCounter = 0, switchFrame = 100, frameSpeed = 500;

    // Functions:
    void textSetUp(sf::Text &text, std::string string, sf::Font font, unsigned int characterSize, sf::Color fillColour,
                   sf::Text::Style style, sf::Vector2f position);
    void textSetUp(sf::Text &text, std::string string, sf::Font font, unsigned int characterSize, sf::Color fillColour,
                   sf::Text::Style style, sf::Vector2f position, sf::Color outlineColour, float outlineThickness);
    void generateRandNoise();
//    void ringUpdate(int ringStage);
    void textSetUp(sf::Text &text, std::string &string, sf::Font &font, unsigned int &characterSize, sf::Color &fillColour,
                   sf::Text::Style &style, sf::Vector2f &position);
    void updateScore();
};


#endif //SK_IVER_GAME_H
