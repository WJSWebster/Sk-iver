//
// Created by William Webster on 15/11/2017.
//
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

#include "HandleEvents.h"
#include "Diver.h"
#include "Background.h"

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
    sf::Vector2u screenDimensions(1080, 920);
    sf::Vector2i blockDimensions(10, 10); // (only used for random noise example)

    sf::RenderWindow window;
    window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "My first SFML Game", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

    sf::Clock clock;
    sf::SoundBuffer soundBuffer; // TODO currently not used
    sf::Sound sound;             // TODO currently not used

    // initialise 'background' object -> TODO make object
    class Background background;

    // initialise 'player' Diver object
    class Diver player;
    player.setTexture("placeholder_spritesheet.png");
    player.setSprite();

    // should just re-assign screenDimension and use here
//    window.setSize(size);
//    window.setTitle("Skᵧ ᴰiver");
    window.setPosition(sf::Vector2i(200, 100));
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
    sf::Text text("Sk-iver", font, 60); // Title
    text.setColor(sf::Color::Magenta); // function deprecated?
    text.setStyle(sf::Text::Bold);
    text.setPosition(300, 50); // TODO needs to be soft-coded, so relative to resolution etc

    sf::CircleShape circle(200, 16); // TODO move into constructor for ring's own class

    sf::View view;
    view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
    view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

    sf::Vector2f viewPosition(0, 0);

    bool quitGame = false;

    while(!quitGame) // beginning of game loop
    {
        quitGame = HandleEvents(window);

        // note: does not work alongside view.reset
        // camera zoom
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            view.zoom(1.01f);  // zooms out
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            view.zoom(0.99f);   // zooms in
        // camera rotate
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            view.rotate(0.5f);  // rotates clockwise
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            view.rotate(-0.5f);   // rotates anti-clockwise

        player.getInputs();
        frameCounter = player.update(clock, frameCounter, frameSpeed);

         // random noise example - todo should move to it's own class and then called to to update/render:
        /* for(int i = 0; i < screenDimensions.x / blockDimensions.x; i++)
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
                }

                window.draw(vertexArray);
            }
        } */

        viewPosition.x = player.getPosition().x + 10 - (screenDimensions.x / 2);
        viewPosition.y = player.getPosition().y + 10 - (screenDimensions.y / 2);

        if(viewPosition.x < 0)
            viewPosition.x = 0;
        if(viewPosition.y < 0)
            viewPosition.y = 0;

        // TODO see https://www.youtube.com/watch?v=pdB7M8J5n-k for better camera centering

//        view.reset(sf::FloatRect(viewPosition.x, viewPosition.y, screenDimensions.x, screenDimensions.y));

        window.setView(view);

        window.draw(background.sprite);
        window.draw(circle);
        window.draw(player.sprite); // this should be a function call to a player.draw() function

//        view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y)); // means that the title stays in a fixed place

        // and the noise background because that was drawn before the view was reset
        window.setView(view);
        window.draw(text);
        window.display();

        window.clear();
    }

    return 0;
}
