//
// Created by William Webster on 15/11/2017.
//
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int main()
{
    sf::Vector2i screenDimension(800,600);

    sf::RenderWindow window;
    window.create(sf::VideoMode(screenDimension.x, screenDimension.y), "My first SFML Game", sf::Style::Titlebar | sf::Style::Close); // | sf::Style::Resize);

    sf::Clock clock;
    sf::SoundBuffer soundBuffer;
    sf::Sound sound;

    sf::Vector2u size(1080, 920);
    window.setSize(size);
//    window.setTitle("Skᵧ ᴰiver");
    window.setPosition(sf::Vector2i(200, 100));
    window.setKeyRepeatEnabled(false); // TODO investigate
    window.setVerticalSyncEnabled(1);
    window.setFramerateLimit(60);

    // loading the player sprite
    sf::Texture playerTexture;
    if(!playerTexture.loadFromFile("placeholder_spritesheet.png")){
        cout << "ERROR: Could not load player image." << endl;
    }


    enum spriteDirection { Down, Left, Right, Up };
    sf::Vector2i source(0, Down);

    sf::Sprite playerImage;
    playerImage.setTexture(playerTexture);

    //Player attributes - to move over to player object once created
    sf::Vector2f position; // player's position
    sf::Vector2f velocity; // player's velocity
    float maxSpeed = 4.0f; // player's maximum speed
    float acceleration = 1.5f; // player's movement acceleration // sk-iver's take a while to get moving
    float deceleration = 0.1f; // player's movement deceleration // sk-iver's stop moving a lot quicker

    while(window.isOpen()) // beginning of game loop
    {
        sf::Event Event;

        while(window.pollEvent(Event))
        {
//          time = clock.getElapsedTime(); // time elapsed since first frame
//          time = clock.restart(); // time elapsed since the last frame rendere
//          cout << time.asSeconds() << endl;

            // should be pushed out to it's own controller function or something
            switch (Event.type)
            {
                case sf::Event::MouseMoved:
//                    cout  << Event.mouseMove.x << ", Y: " << Event.mouseMove.y << endl;
                    break;

                case sf::Event::MouseButtonPressed:
                    if(Event.mouseButton.button == sf::Mouse::Left) // if left mouse button is pressed
                    {
                        cout << "X: " << Event.mouseButton.x << ", Y: " << Event.mouseButton.y;
                    }
                    break;

                case sf::Event::KeyPressed: {
                    // vertical movement
                    // can also be written: if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
                    if (Event.key.code == sf::Keyboard::W or Event.key.code == sf::Keyboard::Up) {
                        cout << "player go up" << endl;

                        source.y = Up;

                        // decrement Diver.y:
                        velocity.y -= acceleration; // apply forward acceleration

                    } else if (Event.key.code == sf::Keyboard::S or Event.key.code == sf::Keyboard::Down) {
                        cout << "player go down" << endl;

                        source.y = Down;


                        // increment Diver.y:
                        velocity.y += acceleration; // apply forward acceleration
                    } else
                        velocity.y *= deceleration;

                    // horizontal movement
                    if (Event.key.code == sf::Keyboard::D or Event.key.code == sf::Keyboard::Right) {
                        cout << "player go right" << endl;


                        source.y = Right;

                        // increment Diver.x:
                        velocity.x += acceleration; // apply rightward acceleration
                    } else if (Event.key.code == sf::Keyboard::A or Event.key.code == sf::Keyboard::Left) {
                        cout << "player go left" << endl;


                        source.y = Left;

                        // increment Diver.x
                        velocity.x -= acceleration; // apply leftward acceleration
                        // velocity.x -= acceleration * deltaTime.restart().asSeconds();
                    } else {
                        velocity.x *= deceleration; // else, not moving horizontally, so apply deceleration (why '*='?)
                    }

                    // now that we've updated our velocity, make sure we're not going beyond max speed:
                    /*if(velocity.x < -maxSpeed)      velocity.x = -maxSpeed;
                    else if(velocity.x > maxSpeed)  velocity.x = maxSpeed;
                    if(velocity.y < -maxSpeed)      velocity.y = -maxSpeed;
                    else if(velocity.y > maxSpeed)  velocity.y = maxSpeed;*/
                    float actualSpeed = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y)); // a*a + b*b = c*c

                    if (actualSpeed > maxSpeed) // are we going too fast?
                    {
                        velocity *= maxSpeed / actualSpeed; // scale our velocity down so we are going at the max speed
                    }

                    // now we have our final velocity, update player's position
                    position += velocity; // update class
                    // extra function call to catch player going off screen
                    //playerImage.setPosition(position); // draw class

                    break;
                }

                case sf::Event::GainedFocus:
                    cout << "Window Active" << endl;
                    // replay audio
                    break;

                case sf::Event::LostFocus:
                    cout << "Window NOT Active" << endl;
                    // pause the game & audio
                    break;

                case sf::Event::Resized:
                    cout << "New width: " << Event.size.width << ", new height: " << Event.size.height << endl;
                    break;

                case sf::Event::Closed:
                {
                    window.close();
                }

                default:
                    cout << endl;
                    break;
            }

        }

        source.x++;
        if(source.x * 256 >= playerTexture.getSize().x)
            source.x = 0;

//        playerImage.setTextureRect(sf::IntRect(source.x * 256, source.y * 256, 256, 256));
        playerImage.setTextureRect(sf::IntRect(source.x * 256, source.y * 256, 256, 256));
        playerImage.setPosition(position);

        window.draw(playerImage);
        window.display();

        window.clear();
    }

    return 0;
}
