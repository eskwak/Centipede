/*
    Edward Kwak
    3/17/2025

    Outline of Spider class.
    
*/

#include <SFML/Graphics.hpp>
#include <random>

#ifndef SPIDER_H
#define SPIDER_H

class Spider {
    private:
        // Spider's sprite
        sf::Sprite spiderSprite;

        // Spider's velocity
        sf::Vector2f spiderVelocity;

        // spider's movement speed
        float speed;

        // spider's sprite texture
        sf::Texture spiderTexture;

    public:
        // Spider constructor
        Spider();

        // updates spider's position
        void update(float dt);

        // gets spider's sprite
        sf::Sprite getSprite();

        // gets spider's global bounds
        sf::FloatRect getBounds();
};

#endif