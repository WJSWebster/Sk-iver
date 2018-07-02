//
// Created by William Webster on 28/06/2018.
//

#include "Game.h"

void Game::setUp() {
    screenDimensions.x = 1920;
    screenDimensions.y = 1280;

    titleString = "Sk-iver";

    // Window:
    window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), titleString,
                  sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    // window.setIcon(32, 32, "");
    window.setPosition(sf::Vector2i(200, 150));
    window.setKeyRepeatEnabled(false); // TODO investigate
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    // Music:
    if(!musicBuffer.loadFromFile("Resources/Sounds/nice_music.ogg")) // if audio file is longer than 30 secs, should probs just stream as Music instead
        std::cout << "ERROR: could not load audio file from file path" << std::endl;

    music.setBuffer(musicBuffer);
    music.setLoop(true);
    music.setVolume(20);
    music.play();

    // Title & Score Font assignment:
    if(!font.loadFromFile("Font/Arial_Unicode.ttf"))
        std::cout << "ERROR: Could not load font file." << std::endl;

    // Title & Score Colour assignment:
    titleColour = scoreColour = sf::Color::White;
    scoreColour = sf::Color::Black;
    scoreColour.a = 150;

    // Title: // TODO check that this works before deleting
    title.setString(titleString);
    title.setFont(font);
    title.setCharacterSize(500);
    title.setFillColor(titleColour);
    title.setStyle(sf::Text::Bold);
    titlePosition.x = (screenDimensions.x - title.getGlobalBounds().width) / 2;
    titlePosition.y = (screenDimensions.y - title.getGlobalBounds().height) / 2;
    title.setPosition(titlePosition);
//    textSetUp(title, titleString, font, 500, titleColour, sf::Text::Bold, titlePosition);

    // Score // TODO check that this works before deleting
    scorePosition.x = (screenDimensions.x - score.getGlobalBounds().width) - 200;
    scorePosition.y = 0;
    updateScore(); // sets score's string & score's position
    score.setFont(font);
    score.setCharacterSize(80);
    score.setFillColor(scoreColour);
    score.setStyle(sf::Text::Italic);

//    score.setOutlineColor(sf::Color::Black);
//    score.setOutlineThickness(5);
//    textSetUp(score, std::to_string(playerScore), font, 80, scoreColour, sf::Text::Italic, scorePosition,
//          sf::Color::Black, 5);

    // Background View:
    backgroundView.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
    backgroundView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

    // Player View:
    playerView.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
    playerView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
}

// text set up for title Text
void Game::textSetUp(sf::Text &text, std::string &string, sf::Font &font, unsigned int &characterSize, sf::Color &fillColour,
                     sf::Text::Style &style, sf::Vector2f &position) {
    text.setString(string);
    text.setFont(font);
    text.setCharacterSize(characterSize);
    text.setFillColor(fillColour);
    text.setStyle(style);
    text.setPosition(position);
}

// text set up for score Text
void Game::textSetUp(sf::Text &text, std::string string, sf::Font font, unsigned int characterSize, sf::Color fillColour,
                     sf::Text::Style style, sf::Vector2f position, sf::Color outlineColour, float outlineThickness) {
    text.setString(string);
    text.setFont(font);
    text.setCharacterSize(characterSize);
    text.setFillColor(fillColour);
    text.setStyle(style);
    text.setPosition(position);
    text.setOutlineColor(outlineColour);
    text.setOutlineThickness(outlineThickness);
}

void Game::update() {
    // todo find a more elegant solution for this
    Diver player = Diver(window.getSize());
    Background background = Background(window.getSize());

    while(!quitGame) // beginning of game loop
    {
        // Get player inputs:
        quitGame = HandleEvents(music, window);

        // camera zoom
        // TODO see https://www.youtube.com/watch?v=pdB7M8J5n-k for better camera centering
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            backgroundView.zoom(1.01f);  // zooms out - todo, limit
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        {
            backgroundView.zoom(0.99f);   // zooms in
        }

        // camera rotate
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            backgroundView.rotate(0.5f);  // rotates clockwise
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            backgroundView.rotate(-0.5f);   // rotates anti-clockwise
        }

        // Background & Noise (update & draw):
        window.setView(backgroundView);

        background.update();
        background.draw(window);

        generateRandNoise();

        // Rings (generateParticles, update & draw):
        if (clock.getElapsedTime().asSeconds() > 9)
        {
            Ring ring = Ring(window.getSize());
            rings.emplace_back(ring);
            clock.restart();
        }

        // todo make two vectors, one for all rings where getStage()<= 1, and those that == 2
        for (auto &ring : rings)
        {
            if(ring.getStage() <= 1)
            {
                int tempScore = ring.update(player);

                // Score update
                if(tempScore)  // i.e. if tempScore != 0
                {
                    playerScore += tempScore;

                    updateScore();
                }

                ring.draw(window);
            }
        }

        // The Player (update & draw):
        window.setView(playerView);

        player.getInputs();
        frameCounter = player.update(clock, frameCounter, frameSpeed);
        player.draw(window);

        // Rings that are in stage 2, ie: now above the player
        window.setView(backgroundView);

        // todo make two vectors, one for all rings where getStage()<= 1, and those that == 2
        for (auto &ring : rings)
        {
            if (ring.getStage() == 2)
            {
                ring.update(player);
                ring.draw(window);
            }
        }


        window.setView(playerView);

        // slowly fades out title - todo: needs to be in it's own title object
        if (textAlpha > 1) // means that title is no longer drawn once no longer visible
        {
            if (clock.getElapsedTime().asSeconds() > 5)
            {
                titleColour.a = static_cast<sf::Uint8>(textAlpha--); // decrements after assignment - this is fine
                title.setFillColor(titleColour);
            }

            window.draw(title);
        }
        else
        {
            window.draw(score);
        }

        window.display();
        window.clear();
    }
}

void Game::updateScore() {
    score.setString(std::to_string(playerScore));

    scorePosition.x = (screenDimensions.x - score.getGlobalBounds().width) - 40;
    score.setPosition(scorePosition);
    std::cout << score.getString().toAnsiString() << "'s global: " << score.getGlobalBounds().width << ", & local: " << score.getLocalBounds().width << std::endl;
}

void Game::generateRandNoise() {
    sf::Vector2i blockDimensions(10, 10); // (only used for random noise example)

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

            for (int k = 0; k < 4; k++)
            {
                int red     = rand() % 255;
                int green   = rand() % 255;
                int blue    = rand() % 255;

                vertexArray[k].color = sf::Color(red, green, blue);
                vertexArray[k].color.a = 30; // sets the alpha
            }

            window.draw(vertexArray);
        }
    }
}

/*void Game::ringUpdate(int ringStage){
    for (auto &ring : rings)
    {
        if(ring.getStage() <= 1)
        {
            playerScore += ring.update(player);
            ring.draw(window);
        }
        else if (ring.getStage() == 2)
        {
            ring.update(player);
            ring.draw(window);
        }
        // else, no ring no longer called so destructor
    }
}*/