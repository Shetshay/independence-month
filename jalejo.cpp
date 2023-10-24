//Author: Justin Alejo
//created on september 27, 2023
#include <GL/glx.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <iostream>
#include "jalejo.h"
#include "classesLander.h"
#include <vector>
using namespace std;

#define rnd() (float)rand() / (float)RAND_MAX

const int NUM_STARS = 100;
Star stars[100];
vector<Asteroid> asteroids;

bool checkCollision(const Lander& spaceship, const std::vector<Asteroid>& asteroids) 
{
	for (const Asteroid& asteroid : asteroids) {
		float distance = sqrt(pow(spaceship.pos[0] - asteroid.x, 2) + pow(spaceship.pos[1] - asteroid.y, 2));
		if (distance < (spaceship.radius + asteroid.radius))
			return true;
	}
	return false;
}

void moveAsteroids() 
{
	for (Asteroid& asteroid : asteroids) {
		asteroid.move();
	}
	if (checkCollision(lander, asteroids)) {
		cout << "Spaceship collided with an asteroid!" << endl;
		g.failed_landing = 1;
	}
}

void render_stars()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POINTS);
	for(int i = 0; i < NUM_STARS; i++){

		glVertex2f(stars[i].x, stars[i].y);

	}
	glEnd();
}

void renderAsteroids() {

	glColor3f(1.0f, 1.0f, 1.0f);
	for (const Asteroid& asteroid : asteroids) {

		glPushMatrix();
		glTranslatef(asteroid.x, asteroid.y, 0.0f);
		glLineWidth(2.0f);
		glBegin(GL_LINES);
			for (int i = 0; i < 25; i++) {
				glColor3ub(255,0,0);
				glVertex2f((rnd() * asteroid.radius * 2) - asteroid.radius, 0.0);
				glColor3ub(250, 250, 0);
				glVertex2f(0.0 + rnd() * 14.0 - 7.0, (50.0 + rnd() * 50.0));
			}
			glEnd();

		glBegin(GL_TRIANGLE_FAN);
		for (int i = 0; i < 360; i += 15) {

			float angle = i * 3.14159265f / 180.0f;
			float x = asteroid.radius * cos(angle);
			float y = asteroid.radius * sin(angle);
			glVertex2f(x,y);
			float t = static_cast<float>(i) / 360.0f;
			float red = 1.0f;
			float green = t;
			glColor3f(red, green, 0.0f);
			glVertex2f(x, y);
		}
		glEnd();
		glPopMatrix();
	}
}
