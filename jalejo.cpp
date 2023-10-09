//Author: Justin Alejo
//created on september 27, 2023
#include <GL/glx.h>
#include <cstdlib>
#include <ctime>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <iostream>
#include "jalejo.h"
using namespace std;


const int NUM_STARS = 100;

Star stars[100];

void render_stars(){

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POINTS);
	for(int i = 0; i < NUM_STARS; i++){

		glVertex2f(stars[i].x, stars[i].y);

	}
	glEnd();
}
