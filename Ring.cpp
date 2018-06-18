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

    srand(time(0)); // used for randomly generating the particles in generateParticles()
}

Ring::~Ring() {
    cout << "Destructor called" << endl;
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
                particles = generateParticles(1000);
                vertices = generateVertices(particles);

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
                for(int i = 0; i < particles.size(); i++)
                {
                    particles[i].update();
                    vertices[i].color = outlineColor;
                    vertices[i].position = particles[i].position;
                }
            } // else ring was not hit - so no particle effect
            break;

        default:
            cout << "ERROR Ring::update: what stage is it now?? " << stage << endl;
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

// Particle Functions:  // TODO this needs to be moved within a particles class of it's own
vector<Particle> Ring::generateParticles(int num)
{
    vector<Particle> particles;
    float radius, theta, x, y;

    for (int i = 0; i < num; i++)
    {
        Particle temp;

        // How quickly the particles expand outwards
        radius = rand() % 3000;
        radius = static_cast<float>((radius / 1000) + 0.005);

        // the number of possible angles that the particles could fly out at
        theta = rand() % 360;

        x = radius * cos(theta);
        y = radius * sin(theta);

        temp.velocity = sf::Vector2f(x, y);
        temp.position = circle.getPosition();

        particles.push_back(temp); // places temp into the vector
    }

    return particles;
}

// draw a vertex at the position of each particle
vector<sf::Vertex /*sf::CircleShape*/> Ring::generateVertices(vector<Particle> particles)
{
    vector<sf::Vertex> vertices;

    for(int i = 0; i < particles.size(); i++)
    {
        sf::Vertex temp;
        temp.position = particles[i].position;
        temp.color = outlineColor;
        // TODO if a vector of sf::CircleShape's instead of sf::Vertex's
//        sf::CircleShape temp;
//        temp.setPosition(particles[i].position);
//        temp.setFillColor(outlineColor);

        vertices.push_back(temp);
    }

    return vertices;
}

void Ring::draw(){
    window.draw(circle);

    if (ringHit) // if there are also particles to draw:
        window.draw(&vertices[0], vertices.size(), sf::Points);
}