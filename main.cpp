//
// Created by William Webster on 15/11/2017.
//
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

#include "HandleEvents.h"
#include "Diver.h"
#include "Background.h"
#include "Ring.h"

#include <iostream>
using namespace std;

#include <string>
#include <math.h>
#include <vector>
#include <chrono> // measures time intervals



// Function Declarations:
//bool handle_events(sf::RenderWindow& window); etc...


// Function Definitions: // TODO should be below the main method
void generateRandNoise();

sf::RenderWindow window;
sf::Vector2u screenDimensions(1920, 1280); // a 3:2 resolution, for 16:9 = (1920, 1080)


int main()
{
    window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Sk-iver", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    // window.setIcon(32, 32, ""); how to convert a png to C sourcecode pixel data?

    sf::Clock clock;

    sf::SoundBuffer soundBuffer;
    sf::Sound sound;

    if(!soundBuffer.loadFromFile("Resources/Sounds/nice_music.ogg")) // if audio file is longer than 30 secs, should probs just stream as Music instead
        cout << "ERROR: could not load audio file from file path" << endl;

    sound.setBuffer(soundBuffer);
    sound.setLoop(true);
    sound.setVolume(20);
    sound.play();

    // initialise 'background' object
    Background background;

    // initialise 'player' Diver object
    Diver player;

//    window.setTitle("Skᵧ ᴰiver");
    window.setPosition(sf::Vector2i(200, 150));
    window.setKeyRepeatEnabled(false); // TODO investigate
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    float frameCounter = 0, switchFrame = 100, frameSpeed = 500;

    // TODO this all needs to be moved into it's own object (& within an init function) for displaying main menu
    sf::Font font;
    if(!font.loadFromFile("Font/Arial_Unicode.ttf"))
        cout << "ERROR: Could not load font file." << endl;
//    basic_string<sf::Uint32> string = {0x53, 0x6B, 0x671D0000, 0x20, 0x1D30, 0x69, 0x76, 0x65, 0x72};
//    sf::String sentence(string);
//    sf::String sentence = "Skᵧ ᴰiver";
    // Title
    sf::Text title("Sk-iver", font, 500);
    sf::Color titleColour = sf::Color::White;
    title.setFillColor(titleColour);
    int textAlpha = 256;
    title.setStyle(sf::Text::Bold);
    float textAnchorX = ((screenDimensions.x - title.getGlobalBounds().width) / 2);
    title.setPosition(textAnchorX, ((screenDimensions.y / 2) - title.getGlobalBounds().height));

    // Score
    int playerScore = 0;
    sf::Text score(to_string(playerScore), font, 80);
    sf::Color scoreColour = titleColour;
    scoreColour.a = 150;
    score.setFillColor(scoreColour);
    score.setStyle(sf::Text::Italic);
//    score.setPosition(screenDimensions.x - score.getGlobalBounds().width, 0);
    score.setOutlineColor(sf::Color::Black);
    score.setOutlineThickness(5);

    //Ring ring;
    vector<Ring> rings; // make a vector, of type 'Ring', called rings

    sf::View backgroundView;
    backgroundView.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
    backgroundView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

    sf::View playerView;
    playerView.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
    playerView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

    bool quitGame = false;

    while(!quitGame) // beginning of game loop
    {
        quitGame = HandleEvents(sound);

        // todo: needs to be moved into event handler

        // camera zoom
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            backgroundView.zoom(1.01f);  // zooms out - todo, limit
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            backgroundView.zoom(0.99f);   // zooms in
        // camera rotate
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            backgroundView.rotate(0.5f);  // rotates clockwise
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            backgroundView.rotate(-0.5f);   // rotates anti-clockwise

        // TODO see https://www.youtube.com/watch?v=pdB7M8J5n-k for better camera centering

        // Background & Noise:
        window.setView(backgroundView);

        background.update();
        background.draw();

        generateRandNoise();

        // Rings (generate, update & draw):
        if (clock.getElapsedTime().asSeconds() > 9)
        {
            Ring ring;
            rings.emplace_back(Ring(ring));
            clock.restart();

        }

        for(int i = 0; i < rings.size(); i++) // TODO: change to foreach loop instead?
        {
            if(rings[i].getStage() <= 1) {
                playerScore += rings[i].update(player);
                rings[i].draw();
            }
        }

        // The Player (update & draw):
        window.setView(playerView);

        player.getInputs(backgroundView);
        frameCounter = player.update(clock, frameCounter, frameSpeed);
        player.draw();

        // Rings that are in stage 2, ie: now above the player
        window.setView(backgroundView);

        for(size_t i = 0; i < rings.size(); i++) { // TODO: change to foreach loop instead?
            if (rings[i].getStage() == 2) {
                rings[i].update(player);
                rings[i].draw();
            }
        }


        window.setView(playerView);

        // slowly fades out title - todo: needs to be in it's own title object
        if (textAlpha > 0) { // means that title is no longer drawn once no longer visible
            if (clock.getElapsedTime().asSeconds() > 5)
            {
                titleColour.a = static_cast<sf::Uint8>(textAlpha--); // decrements after assignment - this is fine
                title.setFillColor(titleColour);
            }

            window.draw(title);
        }
        else {
            score.setString(to_string(playerScore));
            score.setPosition(screenDimensions.x - score.getGlobalBounds().width, 0);

            window.draw(score);
        }

        window.display();

        window.clear();
    }

    return 0;
}

void generateRandNoise() {
    sf::Vector2i blockDimensions(10, 10); // (only used for random noise example)

    for(int i = 0; i < screenDimensions.x / blockDimensions.x; i++)
    {
        for(int j = 0; j < screenDimensions.y / blockDimensions.y; j++)
        {
            sf::VertexArray vertexArray(sf::PrimitiveType::Quads, 4);
            vertexArray[0].position = sf::Vector2f(i * blockDimensions.x, j * blockDimensions.y);
            vertexArray[1].position = sf::Vector2f(i * blockDimensions.x + blockDimensions.x, j * blockDimensions.y);
            vertexArray[2].position = sf::Vector2f(i * blockDimensions.x + blockDimensions.x,
                                                   j * blockDimensions.y + blockDimensions.y);
            vertexArray[3].position = sf::Vector2f(i * blockDimensions.x, j * blockDimensions.y + blockDimensions.y);

            for (int k = 0; k < 4; k++){
                int red     = rand() % 255;
                int green   = rand() % 255;
                int blue    = rand() % 255;

                vertexArray[k].color = sf::Color(red, green, blue);
                vertexArray[k].color.a = 30; // sets the alpha
            }

            window.draw(vertexArray);
        }
    }
}
