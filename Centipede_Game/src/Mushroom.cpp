/*
    Edward Kwak
    3/17/2025

    Implementation of Mushroom class.

*/

#include "Mushroom.h"
#include <cstdlib>
#include <random>

// Mushroom constructor
Mushroom::Mushroom(sf::Texture& firstTexture, sf::Texture& secondTexture, int screenWidth, int screenHeight) {
    firstMushroomTexture = firstTexture;
    secondMushroomTexture = secondTexture;

    mushroomSprite.setTexture(firstTexture);

    hasBeenHit = false;

    std::default_random_engine gen(std::random_device{}());

    std::uniform_int_distribution<> xDist(100, screenWidth - 100);
    std::uniform_int_distribution<> yDist(50, screenHeight - 400);

    this->position.x = xDist(gen);
    this->position.y = yDist(gen);

    mushroomSprite.setPosition(position);
}

// Sets mushroom's position
void Mushroom::setPosition(float x, float y) {
    this -> position.x = x;
    this -> position.y = y;
    mushroomSprite.setPosition(position);
}

// gets mushroom's position
sf::Vector2f Mushroom::getPosition() {
    return position;
}

// gets mushroom's sprite
sf::Sprite Mushroom::getSprite() {
    return mushroomSprite;
}

// gets mushroom sprite's global bounds
sf::FloatRect Mushroom::getBounds() {
    return mushroomSprite.getGlobalBounds();
}

// gets the mushroom's hasBeenHit status
bool Mushroom::getMushroomStatus() {
    return hasBeenHit;
}

// changes mushroom's hasBeenHit status
void Mushroom::mushroomHit() {
    if (hasBeenHit == false) {
        hasBeenHit = true;
    }
}

// changes mushroom's texture after it has been hit
void Mushroom::changeMushroomTexture() {
    mushroomSprite.setTexture(secondMushroomTexture);
}