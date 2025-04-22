/*
    Edward Kwak
    3/17/2025

    Implementation of Spider class.

*/

#include "Spider.h"

// Spider constructor
Spider::Spider() {
    spiderTexture.loadFromFile("graphics/spider.png");
    spiderSprite.setTexture(spiderTexture);
    spiderSprite.setScale(1.0f, 1.0f);
    spiderSprite.setPosition(rand() % 1920, rand() % 1080);
    speed = 100.0f;
}

// updates Spider's position
void Spider::update(float dt) {
    static int frameCount = 0;
    static int randomDirection = rand() % 4;

    // set a delay between switching directions to smooth out spider's movement
    if (frameCount == 45) {
        randomDirection = rand() % 4;
        frameCount = 0;
    }
    frameCount++;

    // up = 0, down = 1, left = 2, right = 3
    if (randomDirection == 0) {
        // move spider up
        spiderSprite.move(0, -4);
    }
    else if (randomDirection == 1) {
        // move spider down
        spiderSprite.move(0, 4);
    }
    else if (randomDirection == 2) {
        // move spider left
        spiderSprite.move(-4, 0);
    }
    else {
        // move spider right
        spiderSprite.move(4, 0);
    }

    // check & handle for spider going out of bounds.
    if (spiderSprite.getPosition().x <= 0) {
        spiderSprite.setPosition(0, spiderSprite.getPosition().y);
    }
    else if (spiderSprite.getPosition().x >= 1920) {
        spiderSprite.setPosition(1920, spiderSprite.getPosition().y);
    }
    else if (spiderSprite.getPosition().y <= 0) {
        spiderSprite.setPosition(spiderSprite.getPosition().x, 0);
    }
    else if (spiderSprite.getPosition().y >= 1080) {
        spiderSprite.setPosition(spiderSprite.getPosition().x, 1080);
    }
}

// gets spider's sprite
sf::Sprite Spider::getSprite() {
    return spiderSprite;
}

// gets spider's global bounds
sf::FloatRect Spider::getBounds() {
    return spiderSprite.getGlobalBounds();
}