/*
    Edward Kwak
    3/17/2025

    Implementation of Laser class.

*/

#include "Laser.h"

// Laser constructor
Laser::Laser(float startX, float startY) {
    position.x = startX;
    position.y = startY;

    laserShape.setSize(sf::Vector2f(5, 20));
    laserShape.setFillColor(sf::Color::Red);
    laserShape.setPosition(position);

    laserSpeed = 650.0f;
}

// updates laser's position 
void Laser::update(float dt) {
    position.y -= laserSpeed * dt;
    laserShape.setPosition(position);
}

// gets laser's position
sf::Vector2f Laser::getPosition() {
    return position;
}

// gets laser's shape
sf::RectangleShape Laser::getShape() {
    return laserShape;
}

// gets laser's global bounds
sf::FloatRect Laser::getBounds() {
    return laserShape.getGlobalBounds();
}


