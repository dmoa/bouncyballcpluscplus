#ifndef SQUARE_H
#define SQUARE_H

#include "SFML/Graphics.hpp"
using namespace sf;

class Square {
public:
    Square();
    Square(float x, float y, int squareLength, float _velocityX, float _velocityY, int _WW, int _WH);
    void move(float dt);
    void changeColor();
    RectangleShape getSquare();
    void flipDirectionX();
    void flipDirectionY();

private:
    float velocityX;
    float velocityY;
    float WW;
    float WH;
    RectangleShape square;
    bool checkWallSideCollision(float dt);
    bool checkCeilFloorCollision(float dt);
};

#endif
