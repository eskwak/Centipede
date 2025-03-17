/*
	Edward Kwak
	3/17/2025

	Implementation of Centipede class.

*/

#include "Centipede.h"

// Implementation centepede constructor
Centipede::Centipede(float startX, float startY, bool isHead) {
	position.x = startX;
	position.y = startY;
	direction = 1;
	this->isHead = isHead;
	if (isHead == true) {
		sprite.setScale(1.0f, 0.88f);
	}
	sprite.setPosition(position);
}

// Setter for the centepede segment's texture
void Centipede::setTexture(sf::Texture& texture) {
	sprite.setTexture(texture);
}

// Getter for centepede's sprite
sf::Sprite Centipede::getSprite() {
	return sprite;
}

// Moves centepede horizontally by offset values
void Centipede::move(float offsetX) {
	sprite.move(offsetX, 0);
	position = sprite.getPosition();
}

// Moves centepede vertically by an offset
void Centipede::moveDown(float offsetY) {
	sprite.move(0.0, offsetY);
	direction = -direction;
	position = sprite.getPosition();
}

// Updates the centepede's sprite position
void Centipede::updatePosition() {
	position = sprite.getPosition();
}

// Set's the direction of the centepede. 1 = right, -1 = left.
void Centipede::setDirection(int d) {
	direction = d;
}

// Getter for the centepede's direction.
int Centipede::getDirection() {
	return direction;
}

// Sets the position of centepede's segment.
void Centipede::setPosition(float x, float y) {
	position.x = x;
	position.y = y;
}

// Retrieves teh centepede's position.
sf::Vector2f Centipede::getPosition() {
	return position;
}

// Checks to see if a centepede segment is a head segment.
bool Centipede::checkIfHead() {
	return isHead;
}

// Changes a body segment to a head segment
void Centipede::changeToHead() {
	if (isHead == false) {
		isHead = true;
	}
}