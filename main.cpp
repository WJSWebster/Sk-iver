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
            if (Event.type == sf::Event::Closed)
            {
                window.close();
            }

//          time = clock.getElapsedTime(); // time elapsed since first frame
            time = clock.restart(); // time elapsed since the last frame rendered
            //        cout << time.asSeconds() << endl;


            if (Event.type == sf::Event::KeyPressed)
            {
                if (Event.key.code == sf::Keyboard::Return)
                {
                    display += message[index];
                    index++;
                    system("clear"); // or system("cls") on windows

                    cout << display;
                }

                // should be pushed out to it's own controller function or something
                switch (Event.type) {
                    case sf::Event::MouseMoved:
                        cout << "X: " << Event.mouseMove.x << ", Y: " << Event.mouseMove.y << endl;
                        break;

                    case sf::Event::MouseButtonPressed:
                        if(Event.mouseButton.button == sf::Mouse::Left)
                        {
                            cout << Event.mouseButton.x << Event.mouseButton.y;
                        }
                        break;

                    case sf::Event::KeyPressed:
                        if (Event.key.code == sf::Keyboard::W or Event.key.code == sf::Keyboard::Up) {
                            cout << "player go up" << endl;
                            // increment Diver.y
                        } else if (Event.key.code == sf::Keyboard::S or Event.key.code == sf::Keyboard::Down) {
                            cout << "player go down" << endl;
                            // decrement Diver.y
                        }

                        if (Event.key.code == sf::Keyboard::D or Event.key.code == sf::Keyboard::Right) {
                            cout << "player go right" << endl;
                            // increment Diver.x
                        } else if (Event.key.code == sf::Keyboard::A or Event.key.code == sf::Keyboard::Left) {
                            cout << "player go left" << endl;
                            // increment Diver.x
                        }

                        break;

                    case sf::Event::Closed:
                        window.close();
                        break;
                }
            }


        }
        window.display();
    }

    return 0;
}
