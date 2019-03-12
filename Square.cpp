#include "Square.h"

Square::Square(float x, float y, int squareLength, float _velocityX, float _velocityY, int _WW, int _WH) {
    square.setPosition(x, y);
    square.setSize(Vector2f(squareLength, squareLength));
    square.setFillColor(Color::Green);
    velocityX = _velocityX;
    velocityY = _velocityY;
    WW = _WW;
    WH = _WH;
}

RectangleShape Square::getSquare() {
    return square;
}

void Square::setPosition(float x, float y){
    square.setPosition(x, y);
}
void Square::setLength(float length){
    square.setSize(Vector2f(length, length));
}
void Square::setVelocity(float velX, float velY){
    velocityX = velX;
    velocityY = velY;
}
void Square::setWorldDimention(float ww, float wh){
    WW = ww;
    WH = wh;
}
void Square::move(float dt) {
    if (checkWallSideCollision(dt)) {
        flipDirectionX();
    }
    if (checkCeilFloorCollision(dt)) {
        flipDirectionY();
    }
    square.setPosition(square.getPosition().x + velocityX * dt, square.getPosition().y + velocityY * dt);
}

bool Square::checkWallSideCollision(float dt) {
	if (square.getPosition().x + square.getSize().x > WW || square.getPosition().x < 0) {
		return true;
	}
	return false;
}

bool Square::checkCeilFloorCollision(float dt) {
	if (square.getPosition().y + square.getSize().y > WH || square.getPosition().y < 0) {
		return true;
	}
	return false;
}

void Square::flipDirectionX(){
    velocityX *=  -1;
}

void Square::flipDirectionY() {
    velocityY *= -1;
}
