//
// Created by William Webster on 15/11/2017.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <ctime>
#include <SFML/Audio.hpp>
#include "Ring.h"
#include "Diver.h"
#include "Particle.h"

using namespace std;

extern sf::RenderWindow window;

Ring::Ring() {
    stage = 0;
    points = 0; // TODO remove points variable and usages

    srand((unsigned int)time(nullptr)); // makes true random (using seed based on curr time)

    x = (float) ((rand() % (window.getSize().x - 325)) + 162.5); // so they dont upscale to be outside of the screen dimensions
    y = (float) ((rand() % (window.getSize().y - 325)) + 162.5);

    cout << "x: " << x << ", y: " << y << endl;

    setSize(150);
    setCurrSize(0); // sets the current radius to 0, and reassigns circle's origin appropriately
    circle.setPosition(x, y);


    outlineColor = sf::Color::Yellow;
    outlineColor.a = 0;

    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(outlineColor);
    circle.setPointCount(10);
    circle.setOutlineThickness(20);


    // Particle Experiment
    ringHit = false;
//    particle.acceleration = sf::Vector2f(0.01, 0.01);
//
//    // TODO this needs to be moved within a particles
//    partCircle.setFillColor(sf::Color::Green);
//    partCircle.setRadius(5);
//    partCircle.setPointCount(5);

        srand(time(0)); // used for randomly generating the particles in generateDots()
}

int Ring::getStage() {
    return stage;
}

void Ring::incrementStage() {
    stage = stage + 1;
}

// TODO: Remove getPoints function and all other references to points var in this class
int Ring::getPoints() {
    return points;
}

// TODO: Remove incPoints function and " "
int Ring::incPoints(int pointInc = 1) {
    points += pointInc;
}

float Ring::getX() const {
    return x;
}

void Ring::setX(int x) {
    Ring::x = x;
    circle.setPosition(x, y);
}

float Ring::getY() const {
    return y;
}

void Ring::setY(int y) {
    Ring::y = y;
    circle.setPosition(x, y);
}

double Ring::getSize() const {
    return size;
}

void Ring::setSize(float size) {
    Ring::size = size;
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
        cout << "ERROR: could not load audio file from file path" << endl;

    hitSound.setBuffer(hitBuffer);
}

void Ring::playHitSound() {
    hitSound.play();
}

void Ring::loadMissSound() {
    if(!missBuffer.loadFromFile("Resources/Sounds/zap.wav")) // if audio file is longer than 30 secs, should probs just stream as Music instead
        cout << "ERROR: could not load audio file from file path" << endl;

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

            if (circle.getOutlineColor().a < 255) { // makes ring gradually more transparent
                makeMoreOpaque();
            }

            if (getCurrSize() >= size) // if circle has reached full size
                incrementStage();

            break;

        case 1 : // when the ring is in the stage of diving through
/*            if ((player.getPosition().x >= circle.getPosition().x) &&
                    (player.getPosition().y >= circle.getPosition().y) &&
                    (player.getPosition().x + player.getSize().x <= circle.getPosition().x + circle.getLocalBounds().width) &&
                    (player.getPosition().y + player.getSize().y <= circle.getPosition().y + circle.getLocalBounds().height) ) { */
            if (player.sprite.getGlobalBounds().intersects(circle.getGlobalBounds())) // TODO: need to make this collision detection more specific
            {
                outlineColor = sf::Color::Green;

                loadHitSound();
                playHitSound();

                ringHit = true;
                dots = generateDots(1000);
                specks = generateSpecks(dots);

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

            if (circle.getOutlineColor().b < 252){
                makeMoreBlue();
            }

            if (circle.getOutlineColor().a >= 2) { // makes ring gradually more transparent
                makeMoreTransparent();
            }
            else
                incrementStage();

            // Particle Experiment
            if (ringHit) // if the player went through the ring (rather than missing it)
            {

//                particle.update();
//                partCircle.setPosition(particle.position); // this should be moved within particle
                cout << "ring hit : " << particle.position.x << ", " << particle.position.y << endl;

                for(int i = 0; i < dots.size(); i++)
                {
                    dots[i].update();
                    specks[i].color = outlineColor;
                    specks[i].position = dots[i].position;
                }
            }
            else
            {
                cout << "ring not hit!" << endl;
            }

            break;

        default:
            cout << "ERROR Ring::update: what stage is it now??" << stage << endl;
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
    // cout << static_cast<int>(circle.getOutlineColor().a);
}

void Ring::makeMoreBlue(){
    outlineColor.b += 2;
    circle.setOutlineColor(outlineColor);
}

vector<Particle> Ring::generateDots(int num)
{
    vector<Particle> parts;
    float radius, theta, x, y;

    for (int i = 0; i < num; i++)
    {
        Particle temp;

        radius = rand() % 1000;
        radius = static_cast<float>((radius / 1000) + 0.005);

//        theta = rand() % 10000; // 10,000 possible angles that the particles could fly out at
        theta = rand() % 360;

        x = radius * cos(theta);
        y = radius * sin(theta);

        temp.velocity = sf::Vector2f(x, y);
        temp.position = circle.getPosition(); // TODO actually pull from circle.getPosition()

        parts.push_back(temp); // places temp into the vector
    }

    return parts;
}

vector<sf::Vertex /*sf::CircleShape*/> Ring::generateSpecks(vector<Particle> dots)
{
    vector<sf::Vertex> verts;

    for(int i = 0; i < dots.size(); i++)
    {
        sf::Vertex temp;
        temp.position = dots[i].position;
        temp.color = outlineColor; // as it should be green by the time this is hit
//        sf::CircleShape temp;
//        temp.setPosition(dots[i].position);
//        temp.setFillColor(outlineColor);

        verts.push_back(temp);
    }

    return verts;
}

void Ring::draw(){
    window.draw(circle);

    if (ringHit)
        window.draw(&specks[0], specks.size(), sf::Points);
}