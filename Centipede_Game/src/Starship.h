/*
    Edward Kwak
    3/17/2025

    Outline of Starship class.
    
*/

#include <SFML/Graphics.hpp>

#ifndef STARSHIP_H
#define STARSHIP_H

class Starship {
    private:
        // starship's position
        sf::Vector2f position;

        // starship's default movement speed
        float starshipSpeed;

        // starship movement flags
        bool starshipMovingRight;
        bool starshipMovingLeft;
        bool starshipMovingUp;
        bool starshipMovingDown;

        // starship firing flag
        bool starshipShooting;

    public:
        // starship constructor
        Starship();

        // sets starship's movement speed
        void setStarshipSpeed(float speed);

        // sets starship's movement flags
        void setStarshipMovingRight(bool flag);
        void setStarshipMovingLeft(bool flag);
        void setStarshipMovingUp(bool flag);
        void setStarshipMovingDown(bool flag);

        // sets starship's shooting flag
        void setStarshipShooting(bool flag);

        // gets starship's movement speed
        float getStarshipSpeed();

        // gets starship's movement flags
        bool getStarshipMovingRight();
        bool getStarshipMovingLeft();
        bool getStarshipMovingUp();
        bool getStarshipMovingDown();

        // get's starship's position
        sf::Vector2f getPosition();

        // get's starship's shooting flag
        bool getStarshipShooting();

        // function to generally update starship's position (dt = delta time)
        void update(float dt); 

        // reset's the starship's position to the starting position
        void resetPosition();
};

#endif