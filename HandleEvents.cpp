//
// Created by William Webster on 30/11/2017.
//

#include "HandleEvents.h"

bool HandleEvents(sf::Sound sound, sf::RenderWindow &window) {
    // poll for events

    sf::Event event{};

    while(window.pollEvent(event))
    {
        // Debug:
//          time = clock.getElapsedTime(); // time elapsed since first frame
//          time = clock.restart(); // time elapsed since the last frame rendered
//          cout << time.asSeconds() << endl;

        switch (event.type)
        {
            // Debug:
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Left) // if left mouse button is pressed
                    std::cout << "X: " << event.mouseButton.x << ", Y: " << event.mouseButton.y << std::endl;
                break;

            case sf::Event::GainedFocus:
                std::cout << "Window Active" << std::endl;
                sound.play();
                break;

            case sf::Event::LostFocus:
                std::cout << "Window NOT Active" << std::endl;
                sound.pause();
                // TODO pause the game mechanics
                break;

            case sf::Event::Resized:
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height))); // letterboxes to keep same original resolution
                std::cout << "New width: " << event.size.width << ", new height: " << event.size.height << std::endl;
                break;

            case sf::Event::Closed:
                window.close();
                return true;

            default: // if other type of pollEvent
                break;
        }

        //

    }

    return false; //true if the user wants to quit the game
};
