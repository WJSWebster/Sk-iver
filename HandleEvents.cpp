//
// Created by William Webster on 30/11/2017.
//

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "HandleEvents.h"

using namespace std;

bool HandleEvents(sf::RenderWindow& window, sf::Sound sound) {
    // poll for events

    sf::Event event;

    while(window.pollEvent(event))
    {
        // Debug:
//          time = clock.getElapsedTime(); // time elapsed since first frame
//          time = clock.restart(); // time elapsed since the last frame rendered
//          cout << time.asSeconds() << endl;

        // TODO should be pushed out to it's own controller function or something
        switch (event.type)
        {
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Left) // if left mouse button is pressed
                    // Debug:
                    cout << "X: " << event.mouseButton.x << ", Y: " << event.mouseButton.y;
                break;

            case sf::Event::GainedFocus:
                cout << "Window Active" << endl;
                sound.play();
                break;

            case sf::Event::LostFocus:
                cout << "Window NOT Active" << endl;
                sound.pause();
                // TODO pause the game mechanics
                break;

            case sf::Event::Resized:
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height))); // letterboxes to keep same original resolution
                cout << "New width: " << event.size.width << ", new height: " << event.size.height << endl;
                break;

            case sf::Event::Closed:
//                window.close();
                return true;

            default: // if other type of pollEvent
                // if window.pollEvent(event) but none of the event types listed here
                break;
        }

    }

    return false; //true if the user wants to quit the game
};
