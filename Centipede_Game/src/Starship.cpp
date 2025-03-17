/*
    Edward Kwak
    3/17/2025

    Implementation of Starship class.

*/

#include "Starship.h"

// implement starship's constructor
Starship::Starship() {
    position.x = 1280 / 2.0f;
    position.y = 720 - 190;

    starshipMovingRight = false;
    starshipMovingLeft = false;
    starshipMovingUp = false;
    starshipMovingDown = false;

    starshipShooting = false;

    starshipSpeed = 400.0f;
}

// Updates starship's position
void Starship::update(float dt) {
    if (starshipMovingRight) {
        position.x += starshipSpeed * dt;
    }
    
    if (starshipMovingLeft) {
        position.x -= starshipSpeed * dt;
    }

    if (starshipMovingUp) {
        position.y -= starshipSpeed * dt;
    }

    if (starshipMovingDown) {
        position.y += starshipSpeed * dt;
    }

    if (position.x < 0) position.x = 0;
    if (position.x > 1280 - 50) position.x = 1280 - 50;
    if (position.y < 0) position.y = 0;
    if (position.y > 720 - 50) position.y = 720 - 50;
}

// sets the starship's speed 
void Starship::setStarshipSpeed(float speed) {
    if (speed >= 1.0f) {
        starshipSpeed = speed;
    }
    else {
        starshipSpeed = 6.0f;
    }
}

// gets spaceship's positin
sf::Vector2f Starship::getPosition() {
    return position;
}

// resets spaceship's position
void Starship::resetPosition() {
    position.x = 1280.0f / 2;
    position.y = 720 - 200;
}

// changes spaceship's right movement status
void Starship::setStarshipMovingRight(bool flag) { starshipMovingRight = flag; }

// changes spaceship's left movement status
void Starship::setStarshipMovingLeft(bool flag) { starshipMovingLeft = flag; }

// changes spaceship's right movement status
void Starship::setStarshipMovingUp(bool flag) { starshipMovingUp = flag; }

// changes spaceship's down movement status
void Starship::setStarshipMovingDown(bool flag) { starshipMovingDown = flag; }

// changes spaceship's shooting status
void Starship::setStarshipShooting(bool flag) { starshipShooting = flag; }

// gets starship's speed 
float Starship::getStarshipSpeed() { return starshipSpeed; }

// gets starship's moving right status
bool Starship::getStarshipMovingRight() { return starshipMovingRight; }

// gets starship's moving left status
bool Starship::getStarshipMovingLeft() { return starshipMovingLeft; }

// gets starship's moving up status
bool Starship::getStarshipMovingUp() { return starshipMovingUp; }

// gets starship's moving down status
bool Starship::getStarshipMovingDown() { return starshipMovingDown; }

// gets starship's shooting status
bool Starship::getStarshipShooting() { return starshipShooting; }