//
// Created by William Webster on 15/11/2017.
//
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

#include <iostream>

using namespace std;

int main(){
//    cout << "Hello, World!" << endl;
//
//    ScreenManager::getInstance().setText("Testing");
//    ScreenManager::getInstance().drawText();
//
//    cin.get(); // waits for input so not to immediately return & end
//    return 0;


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

    cout << "Press a key to continue" << endl;

    while(window.isOpen()) // beginning of game loop
    {
        sf::Event Event;

        while(window.pollEvent(Event))
        {
            if(Event.type == sf::Event::Closed)
                window.close();
        }

//        time = clock.getElapsedTime(); // time elapsed since first frame
        time = clock.restart(); // time elapsed since the last frame rendered
        cout << time.asSeconds() << endl;

        if(window.waitEvent(Event)) // only iterates game loop after an event is processed
        {
            cout << "Event activated" << endl;
        }

        window.display();
    }

    return 0;
}
