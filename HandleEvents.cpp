//
// Created by William Webster on 30/11/2017.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include "HandleEvents.h"

using namespace std;

bool HandleEvents(sf::RenderWindow& window) {
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
            case sf::Event::MouseMoved:
//                    cout  << Event.mouseMove.x << ", Y: " << Event.mouseMove.y << endl;
                break;

            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Left) // if left mouse button is pressed
                    // Debug:
                    cout << "X: " << event.mouseButton.x << ", Y: " << event.mouseButton.y;
                break;

            case sf::Event::GainedFocus:
                cout << "Window Active" << endl;
                // TODO re-play audio etc
                break;

            case sf::Event::LostFocus:
                cout << "Window NOT Active" << endl;
                // TODO pause the game & audio etc
                break;

            case sf::Event::Resized:
//                    window.setView(sf::View(sf::FloatRect(0, 0, Event.size.width, Event.size.height))); // letterboxes to keep same original resolution
                cout << "New width: " << event.size.width << ", new height: " << event.size.height << endl;
                break;

            case sf::Event::Closed:
//                window.close();
                return true;

            default:
                cout << endl;
                break;
        }

    }

    return false; //true if the user wants to quit the game
};
