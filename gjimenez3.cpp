//Gustavo Jimenez
//made 09.29.2023

#include <GL/glx.h>
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <iostream>
#include "gjimenez3.h"
#include "classesLander.h"
#include "log.h"
#include "fonts.h"
#include <vector>
using namespace std;

/*vector<Asteroid> asteroids;

bool checkCollision(const Lander& lander, const std::vector<Asteroid>& asteroids) {
    // Get the boundaries of the lander
    float landerLeft = lander.pos[0] - lander.width / 2;
    float landerRight = lander.pos[0] + lander.width / 2;
    float landerTop = lander.pos[1] + lander.height / 2;
    float landerBottom = lander.pos[1] - lander.height / 2;

    // Check for collision with each asteroid
    for (const Asteroid& asteroid : asteroids) {
        // Get the boundaries of the asteroid
        float asteroidLeft = asteroid.posX - asteroid.radius;
        float asteroidRight = asteroid.posX + asteroid.radius;
        float asteroidTop = asteroid.posY + asteroid.radius;
        float asteroidBottom = asteroid.posY - asteroid.radius;

        // Check for collision by comparing boundaries
        if (landerRight >= asteroidLeft &&
            landerLeft <= asteroidRight &&
            landerTop >= asteroidBottom &&
            landerBottom <= asteroidTop) {
            // Collision detected
            return true;
        }
    }

    // No collision detected
    return false;
}*/
/*
void handleContinueInput(XEvent& e, bool& showContinueScreen, bool& collision, bool& inMenu) {
    if (e.type == KeyPress) {
        if (showContinueScreen) {
            if (e.xkey.keycode == XKeysymToKeycode(x11.getDisplay, XK_y)) {
                // User pressed "c" key to continue the game
                showContinueScreen = false; // Hide the "Continue?" screen
                collision = false; // Reset the collision flag
                lander.pos[0] += lander.vel[0];
				lander.pos[1] += lander.vel[1];
				lander.vel[1] -= GRAVITY;
            } else if (e.xkey.keycode == XKeysymToKeycode(x11.getDisplay, XK_n)) {
                // User pressed "m" key to return to the main menu
                showContinueScreen = false; // Hide the "Continue?" screen
                inMenu = true; // Return to the main menu
                // Handle returning to the main menu here
            }
        }
    }
}

void renderContinueScreen(int countdown) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    // Set the color and text size
    glColor3ub(255, 255, 255);
    Rect r;
    r.bot = 400;
    r.left = 200;
    r.center = 0;

    // Display countdown
    ggprint8b(&r, 16, 0, "CONTINUE?: %d seconds", countdown);

    // Display instructions
    r.bot = 300;
    ggprint8b(&r, 16, 0, "Press 'Y' to continue, 'N' to return to the main menu");
    glPopMatrix();
    x11.swapBuffers();
}*/

void renderPauseScreen() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glColor3ub(255, 255, 255);
    Rect r;
    r.bot = 300;
    r.left = 200;
    r.center = 0;
    //show paused
    ggprint8b(&r, 16, 0x009900FF, "Game Paused");
    glPopMatrix();
    x11.swapBuffers();
}

int keyPressTime(const bool get){
	
	static int keyPress= 1;
	static int startTime;
	if (keyPress){
		startTime= time(NULL);
		keyPress= 0;
	}
	if(get){
	    time_t currentTime = time(NULL);
        return difftime(currentTime, startTime);
    }
    return 0.0;
	
}


void render_space_color()
{
    glPushMatrix();
    	glBegin(GL_QUADS);
    		//Each vertex has a color.
    		glColor3ub(g.purp, 0, g.purp); glVertex2i(0, 0);
    		glColor3ub(g.inversepurp,  0, g.inversepurp); glVertex2i(0, g.yres);
    		glColor3ub(g.purp,  0, g.purp); glVertex2i(g.xres, g.yres);
    		glColor3ub(g.inversepurp, 0,  g.inversepurp); glVertex2i(g.xres, 0);

            if(g.purp == 0) {
                g.isDecreasing = false;
            }
            if (g.purp == 100) {
                g.isDecreasing = true;
            }
            if(g.isDecreasing) {
                g.purp--;
            } else {
                g.purp++;
            }
            g.inversepurp = 100 - g.purp;

    	glEnd();
    	glPopMatrix();
}

void lander_boundaries() 
{
    if (lander.pos[0] < 0)
        lander.pos[0] = g.xres;

    if (lander.pos[0] > g.xres) 
        lander.pos[0] = 0;

    if (lander.pos[1] > g.yres - 30) 
        lander.pos[1] = g.yres - 30;
    
    if (lander.pos[1] < 0)
        g.failed_landing = 1;

    if (lander2.pos[0] < 0)
        lander2.pos[0] = g.xres;

    if (lander2.pos[0] > g.xres) 
        lander2.pos[0] = 0;

    if (lander2.pos[1] > g.yres - 30) 
        lander2.pos[1] = g.yres - 30;
    
    if (lander2.pos[1] < 0)
        g.failed_landing = 1;
}

void render_iceblock () 
{
    	//Draw LZ
	glPushMatrix();
	if(lander.pos[0] <= lz.pos[0] + 20 && lander.pos[0] >= lz.pos[0] - 20 && lander.pos[1] <= lz.pos[1] + 20 && lander.pos[1] >= lz.pos[1] - 20) {
        g.color = 1.0f;
    }
    glColor3ub(173, 216, 230);
    glTranslatef(lz.pos[0], lz.pos[1], 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-lz.width, -lz.height);
    glVertex2f(-lz.width,  lz.height);
    glVertex2f( lz.width,  lz.height);
    glVertex2f( lz.width, -lz.height);
    glEnd();
	glPopMatrix();
}

void moveLz() 
{
    if(g.starsmoveback) {
        lz.moveback();
    } else {
        lz.move();
    }
}

int randnum()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randnum = std::rand() % 401;
    return randnum;
}

void change_value() 
{
    int val = randnum();
    float floatval = static_cast<float>(val);
    lz.pos[0] = floatval;
}

//-----------Landing Zone executables-----
Lz::Lz()
{
    pos[0] = 120.0f;
    pos[1] = 100.0f;
    width = 20.0f;
    height = 20.0f;
}

void Lz::move() 
{
    pos[1] -= 3;
    if (pos[1] < -10) {
    pos[1] = g.yres;
    change_value();
    }
}

void Lz::moveback() 
{
    pos[1] += 3;
    if (pos[1] > g.yres) {
    pos[1] = 0;
    change_value();
    }
}
