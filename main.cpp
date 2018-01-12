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
#include <string>
#include <math.h>
#include <chrono> // measures time intervals

using namespace std;

// Function Declarations:
//bool handle_events(sf::RenderWindow& window); etc...


// Function Definitions: // TODO should be below the main method

int main()
{
    sf::Vector2u screenDimensions(1920, 1280); // a 3:2 resolution, for 16:9 = (1920, 1080)
    sf::Vector2i blockDimensions(10, 10); // (only used for random noise example)

    sf::RenderWindow window;
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
    class Background background(window);

    // initialise 'player' Diver object
    class Diver player(window);


    // should just re-assign screenDimension and use here
//    window.setSize(size);
//    window.setTitle("Skᵧ ᴰiver");
    window.setPosition(sf::Vector2i(200, 150));
    window.setKeyRepeatEnabled(false); // TODO investigate
    window.setVerticalSyncEnabled(1);
    window.setFramerateLimit(60);

    //srand(time(0)); // TODO investigate - is this generating a random seed based on time?

    float frameCounter = 0, switchFrame = 100, frameSpeed = 500;

    // TODO this all needs to be moved into it's own object (& within an init function) for displaying main menu
    sf::Font font;
    if(!font.loadFromFile("Font/Arial_Unicode.ttf"))
        cout << "ERROR: Could not load font file." << endl;
//    basic_string<sf::Uint32> string = {0x53, 0x6B, 0x671D0000, 0x20, 0x1D30, 0x69, 0x76, 0x65, 0x72};
//    sf::String sentence(string);
//    sf::String sentence = "Skᵧ ᴰiver";
    // Title
    sf::Text text("Sk-iver", font, 60);
    sf::Color textColour = sf::Color::Magenta;
    text.setFillColor(textColour);
    int textAlpha = 256;
    text.setStyle(sf::Text::Bold);
    float textAnchorY = (screenDimensions.x / 2) - (text.getLocalBounds().width / 2);
    text.setPosition(textAnchorY, 50);

    //sf::CircleShape circle(200, 16); // TODO move into constructor for ring's own class
    class Ring ring;

    sf::View backgroundView;
    backgroundView.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
    backgroundView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

    sf::View playerView;
    playerView.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
    playerView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

//    sf::Vector2f viewPosition(0, 0);  // todo - no longer used as of implementation of more static camera

    bool quitGame = false;

    while(!quitGame) // beginning of game loop
    {
        quitGame = HandleEvents(window, sound);

        // note: does not work alongside backgroundView.reset
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

//        backgroundView.reset(sf::FloatRect(viewPosition.x, viewPosition.y, screenDimensions.x, screenDimensions.y));

        window.setView(backgroundView);

        background.update();
        background.draw(window);

        // random noise example - todo should move to it's own class and then called to to update/render:
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

        ring.update(player);
        ring.draw(window);


        window.setView(playerView);

        player.getInputs(backgroundView);
        frameCounter = player.update(clock, frameCounter, frameSpeed);
        player.draw(window);

        window.draw(player.sprite); // this should be a function call to a player.draw() function


//        backgroundView.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y)); // means that the title stays in a fixed place

        // and the noise background because that was drawn before the backgroundView was reset
//        window.setView(backgroundView);

        // slowly fades out title - todo: needs to be in it's own text object
        if (clock.getElapsedTime().asSeconds() > 5 and textAlpha > 0){
            textColour.a = textAlpha--; // decrements after assignment - this is fine
            text.setFillColor(textColour);
        }

        window.draw(text);

        window.display();

        window.clear();
    }

    return 0;
}
