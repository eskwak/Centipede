/*
    Edward Kwak
    3/17/2025

    Outline of Mushroom class.
    
*/

#include <SFML/Graphics.hpp>

#ifndef MUSHROOM_H
#define MUSHROOM_H


class Mushroom {
    private:
        // mushroom's sprite
        sf::Sprite mushroomSprite;

        // mushroom's position
        sf::Vector2f position;

        // checks if mushroom has been hit once
        bool hasBeenHit;

        // mushroom's texture before it's hit 
        sf::Texture firstMushroomTexture;

        // mushroom's texture after it's hit
        sf::Texture secondMushroomTexture;

    public:
        // Mushroom constructor
        Mushroom(sf::Texture& firstTexture, sf::Texture& secondTexture, int width, int height);
        
        // Sets mushroom's position
        void setPosition(float x, float y);

        // gets mushroom's position
        sf::Vector2f getPosition();

        // gets mushroom's sprite
        sf::Sprite getSprite();

        // gets sprite's global bounds
        sf::FloatRect getBounds();

        // Changes mushroom's hasBeenHit status
        void mushroomHit();

        // Gets mushroom's hit status
        bool getMushroomStatus();

        // Changes the mushroom's texture after being hit
        void changeMushroomTexture();
};

#endif