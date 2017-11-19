//
// Created by William Webster on 15/11/2017.
//
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

#include <iostream>
#include <string>

using namespace std;

int main(){


    sf::Vector2i screenDimension(800,600);

    sf::RenderWindow window;
    window.create(sf::VideoMode(screenDimension.x, screenDimension.y), "My first SFML Game", sf::Style::Titlebar | sf::Style::Close);


    sf::Clock clock;
    sf::SoundBuffer soundBuffer;
    sf::Sound sound;

    sf::Time time = sf::seconds(2);

    sf::Vector2u size(1080, 920);
//    cout << size.x << " " << size.y << endl; // debug

    window.setSize(size);
    window.setTitle("New Title");
    window.setPosition(sf::Vector2i(200, 100));

    float moveSpeed = 10000.0f;

    string message = "Hello World!";
    string display = "";
    int index = 0;

//    window.setKeyRepeatEnabled(false);

    while(window.isOpen()) // beginning of game loop
    {
        sf::Event Event;

        while(window.pollEvent(Event))
        {
            if(Event.type == sf::Event::Closed)
                window.close();

//          time = clock.getElapsedTime(); // time elapsed since first frame
            time = clock.restart(); // time elapsed since the last frame rendered
    //        cout << time.asSeconds() << endl;


            if(Event.type == sf::Event::KeyPressed)
            {
                if(Event.key.code == sf::Keyboard::Return)
                {
                    display += message[index];
                    index++;
                    system("clear"); // or system("cls") on windows

                    cout << display;
                }

                // should be pushed out to it's own controller function or something
                if((Event.key.code == sf::Keyboard::W) || (Event.key.code == sf::Keyboard::Up))
                {
                    cout << "player go up";
                    // increment Diver.y
                }
                else if((Event.key.code == sf::Keyboard::S) || (Event.key.code == sf::Keyboard::Down))
                {
                    cout << "player go down";
                    // decrement Diver.y
                }

                if((Event.key.code == sf::Keyboard::D) || (Event.key.code == sf::Keyboard::Right))
                {
                    cout << "player go right";
                    // increment Diver.x
                }
                else if((Event.key.code == sf::Keyboard::A) || (Event.key.code == sf::Keyboard::Left))
                {
                    cout << "player go left";
                    // increment Diver.x
                }
            }

        }

        window.display();
    }

    return 0;
}
