/*
	Edward Kwak
	3/17/2025

	Outline of Centipede class.

*/

#include <SFML/Graphics.hpp>
#include <vector>

#ifndef CENTIPEDE_H
#define CENTIPEDE_H

class Centipede {
private:
	// Centepede's sprite. Body segment or Head segment.
	sf::Sprite sprite;

	// Position of centepede.
	sf::Vector2f position;

	// Direction of centepede's travel. 1: right, -1: left.
	int direction;

	// True if a segment is a head segment. False otherwise.
	bool isHead;

public:
	// Centepede constructor
	Centipede(float startX, float startY, bool isHead);

	// Sets centepede texture
	void setTexture(sf::Texture& texture);

	// Retrieves a centepede's sprite
	sf::Sprite getSprite();

	// Moves the centepede horizontally by an offset.
	void move(float offsetX);

	// Moves the centepede vertically by an offset.
	void moveDown(float offsetY);

	// Updates the sprite's position to match centepede's position.
	void updatePosition();

	// Return's centepede's position
	sf::Vector2f getPosition();

	// Sets centepede's position.
	void setPosition(float x, float y);

	// Returns the centepede's direction of travel.
	int getDirection();

	// Sets the centepede's direction of travel.
	void setDirection(int d);

	// Checks if a segment is a head segment.
	bool checkIfHead();

	// Changes a segment to a head segment.	
	void changeToHead();
};

#endif