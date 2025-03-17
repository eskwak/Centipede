/*
    Edward Kwak
    3/18/2025

    Outline of Laser class.
    
*/

#include <SFML/Graphics.hpp>

#ifndef LASER_H
#define LASER_H

class Laser {
    private:
        // laser's shape
        sf::RectangleShape laserShape;

        // laser's position
        sf::Vector2f position;

        // laser's movement speed
        float laserSpeed;
    
    public:
        // laser constructor
        Laser(float startX, float startY);

        // updates the laser's position
        void update(float dt);

        // gets laser's position
        sf::Vector2f getPosition();

        // gets laser's shape
        sf::RectangleShape getShape();

        // gets laser's global bounds
        sf::FloatRect getBounds();
};

#endif