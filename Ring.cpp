//
// Created by William Webster on 15/11/2017.
//

#include "Ring.h"

Ring::Ring() {

    srand((unsigned int)time(nullptr)); // makes true random (using seed based on curr time)

    x = (float) (rand() % (window.getSize().x - 325) + 162.5); // so they dont upscale to be outside of the screen dimensions
    y = (float) (rand() % (window.getSize().y - 325) + 162.5);
    std::cout << "x: " << x << ", y: " << y << std::endl;

    setCurrSize(0); // sets the current radius to 0, and reassigns circle's origin appropriately
    circle.setPosition(x, y);

    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(outlineColor);
    circle.setPointCount(10);
    circle.setOutlineThickness(20);

    particles.generateParticles(1000, circle);
}

Ring::~Ring() {
    std::cout << "Ring Destructor" << std::endl;
}

int Ring::getStage() {
    return stage;
}

void Ring::incrementStage() {
    stage = stage + 1;
}

float Ring::getCurrSize() const {
    return circle.getRadius();
}

void Ring::setCurrSize(float currSize) {
    circle.setRadius(currSize);
    resetOrigin();
}

void Ring::resetOrigin() {
    circle.setOrigin(circle.getRadius(), circle.getRadius());
}

void Ring::loadHitSound() {
    if(!hitBuffer.loadFromFile("Resources/Sounds/jump.wav")) // if audio file is longer than 30 secs, should probs just stream as Music instead
    {
        std::cout << "ERROR: could not load audio file from file path" << std::endl;
    }

    hitSound.setBuffer(hitBuffer);
}

void Ring::playHitSound() {
    hitSound.play();
}

void Ring::loadMissSound() {
    if(!missBuffer.loadFromFile("Resources/Sounds/zap.wav")) // if audio file is longer than 30 secs, should probs just stream as Music instead
    {
        std::cout << "ERROR: could not load audio file from file path" << std::endl;
    }

    missSound.setBuffer(missBuffer);
}

void Ring::playMissSound() {
    missSound.play();
}

int Ring::update(Diver player){
    float tempSize = getCurrSize();
    int score = 0;

    switch(stage) {
        case 0 :
            tempSize += 0.5;
            setCurrSize(tempSize);

            if (getCurrSize() >= size) // if circle has reached full size
            {
                incrementStage();
            }
            else if (circle.getOutlineColor().a < 255) // makes ring gradually more transparent
            {
                makeMoreOpaque();
            }

            break;

        case 1 : // when the ring is in the stage of diving through
            if (player.sprite.getGlobalBounds().intersects(circle.getGlobalBounds())) // TODO: need to make this collision detection more specific
            {
                outlineColor = sf::Color::Green;

                loadHitSound();
                playHitSound();

                ringHit = true;

                score++;
            }
            else // if player does not intersect with the ring
            {
                outlineColor = sf::Color::Red;

                loadMissSound();
                playMissSound();
            }

            incrementStage();

            break;

        case 2 : // when the ring has flown past the diver
            tempSize += 1.5;
            setCurrSize(tempSize);

            if (circle.getOutlineColor().b < 252)
            {
                makeMoreBlue();
            }

            if (circle.getOutlineColor().a >= 2) // makes ring gradually more transparent
            {
                makeMoreTransparent();

                // Particle Experiment
                if (ringHit) // if the player went through the ring (rather than missing it)
                {
                    particles.update(outlineColor);
                } // else ring was not hit - so no particle effect
            }
            else
            {
                incrementStage(); // kill ring
            }

            break;

        default:
            std::cout << "ERROR Ring::update: what stage is it now?? " << stage << std::endl;
            break;
    }

    return score;
}

void Ring::makeMoreOpaque(){
    outlineColor.a += ceil(0.85); // outlineColor.a is type int - this will always inc by 1
    circle.setOutlineColor(outlineColor);
}

void Ring::makeMoreTransparent(){
    outlineColor.a -= 2; // outlineColor.a is type int
    circle.setOutlineColor(outlineColor);
}

void Ring::makeMoreBlue(){
    outlineColor.b += 2;
    circle.setOutlineColor(outlineColor);
}

void Ring::draw(){
    window.draw(circle);

    if (ringHit) // if there are also particles to draw:
    {
        particles.draw();
    }
}