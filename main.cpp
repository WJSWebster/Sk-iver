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
    sf::Vector2i screenDimensions(800, 600);
    sf::Vector2i blockDimensions(10, 10); // (only used for random noise example)

    sf::RenderWindow window;
    window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "My first SFML Game", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

    sf::Clock clock;
    sf::SoundBuffer soundBuffer; // TODO currently not used
    sf::Sound sound;             // TODO currently not used

//    should just re-assign screenDimension and use here

    sf::Vector2u size(1080, 920);
    window.setSize(size);
//    window.setTitle("Skᵧ ᴰiver");
    window.setPosition(sf::Vector2i(200, 100));
//    window.setKeyRepeatEnabled(false); // TODO investigate
    window.setVerticalSyncEnabled(1);
    window.setFramerateLimit(60);

    //srand(time(0)); // TODO investigate - is this generating a random seed based on time?

    float frameCounter = 0, switchFrame = 100, frameSpeed = 500;

    // loading the player sprite
    sf::Texture playerTexture;
    if(!playerTexture.loadFromFile("placeholder_spritesheet.png"))
        cout << "ERROR: Could not load player image." << endl;

    sf::Sprite playerImage;
    playerImage.setTexture(playerTexture);

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

    enum spriteDirection { Down, Left, Right, Up };
    sf::Vector2i source(0, Down);

    //Player attributes - to move over to player object once created
    sf::Vector2f position; // player's position
    sf::Vector2f velocity; // player's velocity
    float maxSpeed = 4.0f; // player's maximum speed
    float acceleration = 0.5f; // player's movement acceleration // sk-iver's take a while to get moving // (previously 1.1f)
    float deceleration = 0.98f; // player's movement deceleration // sk-iver's stop moving a lot quicker

    sf::CircleShape circle(200, 16); // TODO move into constructor for ring's own class

    while(window.isOpen()) // beginning of game loop
    {
        sf::Event Event;

        while(window.pollEvent(Event))
        {
            // Debug:
//          time = clock.getElapsedTime(); // time elapsed since first frame
//          time = clock.restart(); // time elapsed since the last frame rendered
//          cout << time.asSeconds() << endl;

            // TODO should be pushed out to it's own controller function or something
            switch (Event.type)
            {
                case sf::Event::MouseMoved:
//                    cout  << Event.mouseMove.x << ", Y: " << Event.mouseMove.y << endl;
                    break;

                case sf::Event::MouseButtonPressed:
                    if(Event.mouseButton.button == sf::Mouse::Left) // if left mouse button is pressed
                        // Debug:
                        cout << "X: " << Event.mouseButton.x << ", Y: " << Event.mouseButton.y;
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
                    cout << "New width: " << Event.size.width << ", new height: " << Event.size.height << endl;
                    break;

                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    cout << endl;
                    break;
            }

        }

        // vertical movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) or sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            source.y = Up;

            velocity.y -= acceleration; // apply forward acceleration by decrementing y velocity

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) or sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            source.y = Down;

            velocity.y += acceleration; // apply backward acceleration by incrementing y velocity
        } else
            velocity.y *= deceleration; // decelerate

        // horizontal movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            source.y = Right;

            velocity.x += acceleration; // apply rightward acceleration
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            source.y = Left;

            velocity.x -= acceleration; // apply leftward acceleration
            // velocity.x -= acceleration * deltaTime.restart().asSeconds();
        } else {
            velocity.x *= deceleration; // else, not moving horizontally, so apply deceleration (why '*='?)
        }

        // now that we've updated our velocity, make sure we're not going beyond max speed:
        float actualSpeed = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y)); // a*a + b*b = c*c

        if (actualSpeed > maxSpeed) // are we going too fast?
            velocity *= maxSpeed / actualSpeed; // scale our velocity down so we are going at the max speed

        // now we have our final velocity, update player's position
        position += velocity; // TODO update class
        // TODO extra function call to catch player going off screen

        // "* clock.restart().asSeconds" keeps the animation consistent through realtime, rather than depending on cpu's clockspeed
        frameCounter += frameSpeed * clock.restart().asSeconds();
        // if 500 frames have passed, cycle through to next animation
        if (frameCounter >= switchFrame){
            // animation of sprite through SS images, based on which direction facing
            source.x++;
            if(source.x * 256 >= playerTexture.getSize().x)
                source.x = 0;

            frameCounter = 0;
        }

        playerImage.setTextureRect(sf::IntRect(source.x * 256, source.y * 256, 256, 256));
        playerImage.setPosition(position);

        // random noise example:
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
                    int red = rand() % 255;
                    int green = rand() % 255;
                    int blue = rand() % 255;

                    vertexArray[k].color = sf::Color(red, green, blue);
                }

                window.draw(vertexArray);
            }
        }

        window.draw(circle);
        window.draw(playerImage);
        window.draw(text);
        window.display();

        window.clear();
    }

    return 0;
}
