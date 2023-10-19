// modified by group 2 // andrew, justin, gus, john, jacob
//
//author: Gordon Griesel
//date: Fall 2023
//purpose: 1. learn OpenGL
//         2. write an aerospace related program
//         3. prepare to apply for a job at SpaceX
//
//This is a game in which we try to land the rocket booster back on
//the launch pad. You must add code to check for a good landing, and
//also show the rocket landed and secure on the pad.
//
//If the rocket doesn't land safely, then you can show some kind of
//explosion or whatever.
//
#include <iostream>
using namespace std;
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "aibrahim.h"
#include "classesLander.h"//classes deleted and put in classesLander.h
#include "jalejo.h"
#include <vector>
#include "jacosta.h"
#include "fonts.h"
#include "log.h"
Global g;
Lz1 lz1;
Lz2 lz2;
Lz3 lz3;
Lz4 lz4;
Lz5 lz5;
Lander lander;
X11_wrapper x11;
//---Justin's extern and function declarations---//
extern struct Star stars[100];
const int NUM_STARS = 100;
extern vector<Asteroid> asteroids;
void moveAsteroids();
bool checkCollision(const Lander& spaceship, const std::vector<Asteroid>& asteroids) {
	for (const Asteroid& asteroid : asteroids) {
		float distance = sqrt(pow(spaceship.pos[0] - asteroid.x, 2) + pow(spaceship.pos[1] - asteroid.y, 2));
		if (distance < (spaceship.radius + asteroid.radius))
			return true;
	}
	return false;
}
void moveAsteroids() {
	for(Asteroid& asteroid : asteroids) {
		asteroid.move();
	}
	if(checkCollision(lander, asteroids)) {
		cout << "Spaceship collided with an asteroid!" << endl;
		g.failed_landing = 1;
	}
}
//----------------------------------//

//floating point random numbers
#define rnd() (float)rand() / (float)RAND_MAX

//gravity pulling the rocket straight down
const float GRAVITY = 0.007;

//Function prototypes
void init_opengl(void);
void physics(void);
void render(void);



//=====================================
// MAIN FUNCTION IS HERE
//=====================================
int main()
{	
	bool inMenu = true;//bool for menu handling

	logOpen();
	init_opengl();
	printf("Press T or Up-arrow for thrust.\n");
	printf("Press Left or Right arrows for rocket thrust vector.\n");
	//Justin--initializing asteroids---------------------//
	srand(time(NULL));
	for (int i = 0; i < 5; ++i) {

		float startX = rand() % g.xres;
		float startY = rand() % g.yres;
		float startRadius = rand() % 20 + 10;
		float startSpeed = rand() % 4 + 1;
		asteroids.push_back(Asteroid(startX, startY, startRadius, startSpeed));
	}
	//---------------------------------------------------//
	//Main loop

	int done = 0;
	while (!done) {
		//Process external events.
		while (x11.getXPending()) {
			XEvent e = x11.getXNextEvent();
			x11.check_resize(&e);
			x11.check_mouse(&e);
			done = x11.check_keys(&e);
		}
		// logic for game menu
		if(!inMenu){
		physics();
		render();
		x11.swapBuffers();
		usleep(400);
		}else{// if inMenu true display and turn inMenu false
		handleMenu();
		inMenu = !inMenu;
	}
}
	cleanup_fonts();
	logClose();
	return 0;
}

void init_opengl(void)
{
	//OpenGL initialization
	glViewport(0, 0, g.xres, g.yres);
	//Initialize matrices
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	//Set 2D mode (no perspective)
	glOrtho(0, g.xres, 0, g.yres, -1, 1);
	//Set the screen background color
	glClearColor(0.1, 0.1, 0.1, 1.0);
	glEnable(GL_TEXTURE_2D);
    initialize_fonts();
	//----Adding Star Code-------//
	glBegin(GL_POINTS);
	srand(time(NULL));
	for(int i = 0; i < NUM_STARS; i++) {
		float x = static_cast<float>(rand() % g.xres);
		float y = static_cast<float>(rand() % g.yres);
		stars[i] = Star(x,y);
	}
}

void physics()
{
	//Lander physics
	if (g.failed_landing)
	 return;
	lander.pos[0] += lander.vel[0];
	lander.pos[1] += lander.vel[1];
	lander.vel[1] -= GRAVITY;
	//lz.pos[0] += 0.6f;

	lz1.pos[1] -= 0.3f; //lander 1 decrease
	lz2.pos[1] -= 0.4f; //lander 2 decrease
	lz3.pos[1] -= 0.3f; //lander 3 decrease
	lz4.pos[1] -= 0.3f; //lander 4 decrease
	lz5.pos[1] -= 0.5f; //lander 5 decrease //will add code around here

	//apply thrust
	//convert angle to radians...
	float ang = ((lander.angle+90.0) / 360.0) * (3.14159 * 2.0);
	//make a thrust vector...
	float xthrust = cos(ang) * lander.thrust;
	float ythrust = sin(ang) * lander.thrust;
	lander.vel[0] += xthrust;
	lander.vel[1] += ythrust;
	lander.thrust *= 0.95f;
	if (g.keys[XK_t] || g.keys[XK_Up]) {
		//Thrust for the rocket, and movement of stars
		lander.thrust = 0.02;
		for (int i = 0; i < 100; i++) {
			stars[i].y -= 2.0f;
			if (stars[i].y < 0)
				stars[i].y = g.yres;
		}
	}
	if (g.keys[XK_Left])
		lander.angle += 0.9;
	if (g.keys[XK_Right])
		lander.angle -= 0.9;

	for (int j = 0; j < 100; j++) {
		stars[j].y -= 1.0f;
		if (stars[j].y < 0)
			stars[j].y =  g.yres;
	}

handle_landerInter();

spawn_newLander();
}
void render()
{

	glClear(GL_COLOR_BUFFER_BIT);
	

	renderAsteroids();
	moveAsteroids();
	render_stars();

	//Draw LZ
	if (g.color_reset == 1)
		glColor3ub(0, 0, 0);

	glPushMatrix();
	glColor3ub(250, 250, 20);                                       
	glTranslatef(lz1.pos[0]=g.nxtlanderX1, lz1.pos[1], 0.0f); //Lander spawning
	glBegin(GL_QUADS);
	glVertex2f(-lz1.width, -lz1.height);
	glVertex2f(-lz1.width,  lz1.height);
	glVertex2f( lz1.width,  lz1.height);
	glVertex2f( lz1.width, -lz1.height);
	glEnd();
	glPopMatrix();




	//SECOND PLATFORM
	if (g.color_reset == 1) {
		glColor3ub(0, 0, 0);
	}
glPushMatrix();
glColor3ub(250, 250, 20);                             
glTranslatef(lz2.pos[0]=g.nxtlanderX2, lz2.pos[1], 0.0f); //Lander spawning
glBegin(GL_QUADS);
glVertex2f(-lz1.width, -lz1.height);
glVertex2f(-lz1.width,  lz1.height);
glVertex2f( lz1.width,  lz1.height);
glVertex2f( lz1.width, -lz1.height);
glEnd();
glPopMatrix();


//THIRD PLATFORM
if (g.color_reset == 1) {
	glColor3ub(0, 0, 0);
}
glPushMatrix();
glColor3ub(250, 250, 20);                             
glTranslatef(lz3.pos[0]=g.nxtlanderX3, lz3.pos[1], 0.0f); //Lander spawning
glBegin(GL_QUADS);
glVertex2f(-lz1.width, -lz1.height);
glVertex2f(-lz1.width,  lz1.height);
glVertex2f( lz1.width,  lz1.height);
glVertex2f( lz1.width, -lz1.height);
glEnd();
glPopMatrix();



//FOURTH PLATFORM
if (g.color_reset == 1) {
	glColor3ub(0, 0, 0);
}
glPushMatrix();
glColor3ub(250, 250, 20);                             
glTranslatef(lz4.pos[0]=g.nxtlanderX4, lz4.pos[1], 0.0f); //Lander spawning
glBegin(GL_QUADS);
glVertex2f(-lz1.width, -lz1.height);
glVertex2f(-lz1.width,  lz1.height);
glVertex2f( lz1.width,  lz1.height);
glVertex2f( lz1.width, -lz1.height);
glEnd();
glPopMatrix();


//FIFTH PLATFORM
if (g.color_reset == 1) {
	glColor3ub(0, 0, 0);
}
glPushMatrix();
glColor3ub(250, 250, 20);                             
glTranslatef(lz5.pos[0]=g.nxtlanderX5, lz5.pos[1], 0.0f); //Lander spawning
glBegin(GL_QUADS);
glVertex2f(-lz1.width, -lz1.height);
glVertex2f(-lz1.width,  lz1.height);
glVertex2f( lz1.width,  lz1.height);
glVertex2f( lz1.width, -lz1.height);
glEnd();
glPopMatrix();





//Draw Lander
glPushMatrix();
glColor3ub(250, 250, 250);
if (g.failed_landing) {
	glColor3ub(250, 0, 0); //Red color USLEEP WHILE LOOP TO INDICATE LIFE LOST
			       //if (g.landed == 1){
			       //	glColor3ub(0, 250, 0); //Green color
}
/*if (g.landed == 0) {
	glColor3ub(250,250,250); 
}*/
glTranslatef(lander.pos[0], lander.pos[1], 0.0f);
glRotated(lander.angle, 0.0, 0.0, 1.0);
glBegin(GL_TRIANGLES);
for (int i=0; i<3; i++) {
	glVertex2f(lander.verts[i][0], lander.verts[i][1]);
}
glEnd();
//Lander thrust
if (lander.thrust > 0.0) {
	//draw the thrust vector
	glBegin(GL_LINES);
	for (int i=0; i<25; i++) {
		glColor3ub(0, 0, 255);
		glVertex2f(rnd()*10.0-5.0, 0.0);
		glColor3ub(250, 250, 0);
		glVertex2f(0.0+rnd()*14.0-7.0,
				lander.thrust * (-4000.0 - rnd() * 2000.0));
	}
	glEnd();
}
if (g.failed_landing) {
	//show crash graphics here...

}
glPopMatrix();
}






