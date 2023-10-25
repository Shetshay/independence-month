//Author: Justin Alejo
//Created on 9/29/2023
#ifndef _JALEJO_H
#define _JALEJO_H

#include <iostream>
#include <vector>
using namespace std;

extern void render_stars();
extern void renderAsteroids();
extern void moveAsteroids();
extern bool checkCollision();
extern int mouse_time();

struct Star{

	float x, y;
	Star() {
		x = 0.0f;
		y = 0.0f;
	}
	Star(float ex, float why){
		x = ex;
		y = why;
	}
};

class Asteroid{

	public:
	float x, y;
	float radius;
	float speed;
	Asteroid(float startX, float startY, float startRadius, float startSpeed) {
		x = startX;
		y = startY;
		radius = startRadius;
		speed = startSpeed;
	}

	void move() {
		y -= speed;
		if (y < 0){
		reset();
		}
	}

	void reset() {
		x = rand() % 400;
		y = 600 + radius;
	}

};



#endif
