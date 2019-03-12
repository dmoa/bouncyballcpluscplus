#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include "Square.h"
using namespace sf;


const int WW = 300;
const int WH = 300;

const int squareLength = 20;

bool checkCollision(float coord, float coord2, float velocity1, float velocity2, float dt);
bool checkVelocitiesRight(float xv, float xv2);
bool checkVelocitiesLeft(float xv, float xv2);
bool checkVelocitiesUp(float yv, float yv2);
bool checkVelocitiesDown(float yv, float yv2);
bool checkWallSideCollision(float squarex, float squarexv, float dt);
bool checkCeilFloorCollision(float squarey, float squareyv, float dt);

int main(int argc, char ** argv) {
	sf::RenderWindow renderWindow(VideoMode(WW, WH), "Bouncy Ball");

	sf::Event event;
	sf::Clock clock;

	Music music;
	if (!music.openFromFile("main.ogg")) {
	}
	music.play();


	Square greenSquare(50.0, 50.0, squareLength, 110.0, 100.0, WW, WH);


	int numberOfSquares = 6;
	RectangleShape squares[numberOfSquares];
	float squaresVelocity[numberOfSquares][2];

	for (int i = 0; i < numberOfSquares; i++) {
		srand((int)time(0) * 17 * i);
		int x = rand() % WW;
		srand((int)time(0) * 22 * i);
		int y = rand() % WH;
		bool overlapping = true;
		while (overlapping) {
			overlapping = false;
			for (int j = 0; j < i; j++) {
				bool xcollision = checkCollision(squares[j].getPosition().x, x, 0, 0, 0);
				bool ycollision = checkCollision(squares[j].getPosition().y, y, 0, 0, 0);
				if (xcollision && ycollision) {
					overlapping = true;
					srand((int)time(0) * (i + j) * (i + j));
					x = rand() % WW;
					y = rand() % WH;
				}
			}
		}
		srand((int)time(0) * 765 * i);
		int vx =  rand() % 500 + 100;
		srand((int)time(0) * 31 * i);
		int vy =  rand() % 500 + 100;
		if (i < numberOfSquares / 2) {
			squares[i].setFillColor(Color::Blue);
		} else {
			squares[i].setFillColor(Color::Red);
		}
		squares[i].setPosition(x, y);
		squares[i].setSize(Vector2f(squareLength, squareLength));
		squaresVelocity[i][0] = vx;
		squaresVelocity[i][1] = vy;
	}

	while(renderWindow.isOpen()) {
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed) {
				renderWindow.close();
			}
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Key::Escape) {
					renderWindow.close();
				}
				if (event.key.code == Keyboard::Key::C) {
					for (int i = 0; i < numberOfSquares; i++) {
						if (squares[i].getFillColor() == Color::Blue) {
							squares[i].setFillColor(Color::Red);
						} else {
							squares[i].setFillColor(Color::Blue);
						}
					}
				}
			}
		}

		Time deltaTime = clock.restart();

		for (int i = 0; i < numberOfSquares; i++) {
			bool wallCheck = checkWallSideCollision(squares[i].getPosition().x, squaresVelocity[i][0], deltaTime.asSeconds());
			if (wallCheck) {
				if (squares[i].getPosition().x > WW - squareLength) {
					squares[i].setPosition(WW - squareLength, squares[i].getPosition().y);
				} else {
					squares[i].setPosition(0, squares[i].getPosition().y);
				}
				squaresVelocity[i][0] *= -1;
			}

			bool ceilfloorCheck = checkCeilFloorCollision(squares[i].getPosition().y, squaresVelocity[i][1], deltaTime.asSeconds());
			if (ceilfloorCheck) {
				if (squares[i].getPosition().y > WH - squareLength) {
					squares[i].setPosition(squares[i].getPosition().x, WH - squareLength);
				} else {
					squares[i].setPosition(squares[i].getPosition().x, 0);
				}
				squaresVelocity[i][1] *= -1;
			}

			squares[i].setPosition(squares[i].getPosition().x + squaresVelocity[i][0] * deltaTime.asSeconds(), squares[i].getPosition().y + squaresVelocity[i][1] * deltaTime.asSeconds());

			for (int j = i + 1; j < numberOfSquares; j++) {
				bool overlappingX = checkCollision(squares[i].getPosition().x, squares[j].getPosition().x, squaresVelocity[i][0],  squaresVelocity[j][0], deltaTime.asSeconds());
				bool overlappingY = checkCollision(squares[i].getPosition().y, squares[j].getPosition().y, squaresVelocity[i][1],  squaresVelocity[j][1], deltaTime.asSeconds());
				if (overlappingX && overlappingY) {


					if (squares[i].getFillColor() == Color::Blue) {
						squares[i].setFillColor(Color::Red);
					} else {
						squares[i].setFillColor(Color::Blue);
					}

					if (squares[j].getFillColor() == Color::Blue) {
						squares[j].setFillColor(Color::Red);
					} else {
						squares[j].setFillColor(Color::Blue);
					}


					if (checkVelocitiesRight(squaresVelocity[i][0], squaresVelocity[j][0])) {
						if (squaresVelocity[i][0] > squaresVelocity[j][0]) {
							squaresVelocity[i][0] *= -1;
						} else {
							squaresVelocity[j][0] *= -1;
						}
					} else if (checkVelocitiesLeft(squaresVelocity[i][0], squaresVelocity[j][0])) {
						if (squaresVelocity[i][0] < squaresVelocity[j][0]) {
							squaresVelocity[i][0] *= -1;
						} else {
							squaresVelocity[j][0] *= -1;
						}
					} else {
						squaresVelocity[i][0] *= -1;
						squaresVelocity[j][0] *= -1;
					}

					if (checkVelocitiesUp(squaresVelocity[i][1], squaresVelocity[j][1])) {
						if (squaresVelocity[i][1] > squaresVelocity[j][1]) {
							squaresVelocity[i][1] *= -1;
						} else {
							squaresVelocity[j][1] *= -1;
						}
					} else if (checkVelocitiesDown(squaresVelocity[i][1], squaresVelocity[j][1])) {
						if (squaresVelocity[i][1] > squaresVelocity[j][1]) {
							squaresVelocity[i][1] *= -1;
						} else {
							squaresVelocity[j][1] *= -1;
						}
					} else {
						squaresVelocity[i][1] *= -1;
						squaresVelocity[j][1] *= -1;
					}

				}
			}
		}



		renderWindow.clear();
		for (int i = 0; i < numberOfSquares; i++) {
			//	printf("square %i x: %f y: %f \n", i, squares[i].getPosition().x, squares[i].getPosition().y);
			renderWindow.draw(squares[i]);
		}
		greenSquare.move(deltaTime.asSeconds());
		renderWindow.draw(greenSquare.getSquare());

		renderWindow.display();
	}
}

bool checkWallSideCollision(float squarex, float squarexv, float dt) {
	if (squarex + squareLength > WW || squarex < 0) {
		return true;
	}
	return false;
}

bool checkCeilFloorCollision(float squarey, float squareyv, float dt) {
	if (squarey + squareLength > WH || squarey < 0) {
		return true;
	}
	return false;
}

bool checkCollision(float coord, float coord2, float velocity1, float velocity2, float dt) {
	bool check1 = coord + squareLength + (velocity1 * dt) > coord2 + (velocity2 * dt);
	bool check2 = coord + (velocity1 * dt) < coord2 + squareLength + (velocity2 * dt);
	return (check1 && check2);
}

//to return 3
int getthree(int number) {
	if (number == 3) {
		return number;
	} else {
		return 3;
	}
}

bool checkVelocitiesRight(float xv, float xv2) {
	if(xv > 0 && xv2 > 0) {
		return true;
	}
	return false;
}

bool checkVelocitiesLeft(float xv, float xv2) {
	if(xv < 0 && xv2 < 0) {
		return true;
	}
	return false;
}


bool checkVelocitiesUp(float yv, float yv2) {
	if(yv > 0 && yv2 > 0) {
		return true;
	}
	return false;
}

bool checkVelocitiesDown(float yv, float yv2) {
	if(yv < 0 && yv2 < 0) {
		return true;
	}
	return false;
}
