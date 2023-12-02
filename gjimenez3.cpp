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

void renderContinueScreen() {
    // Render "Continue?" message
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    // Set the color and text size
    glColor3ub(255, 255, 255);
    int windowWidth = g.xres;
    int windowHeight = g.yres;
    Rect r;
    r.bot = windowHeight / 2;
    r.left = windowWidth / 4;
    r.center = 0;

    if(g.countdown > 0){
        //countdown has time in between seconds
        if(timerCountdown(1)){
        g.countdown--;
        }
    }
    //render continue
    ggprint13(&r, 20, 0x00ffff00, "Continue?");
    
    //render countdown
    ggprint13(&r, 20, 0x00ffff00, "Countdown: %d", g.countdown);

    //render options
    ggprint13(&r, 20, 0x00ffff00, "Press C to Retry or");
    ggprint13(&r, 20, 0x00ffff00, "M to go back to Main Menu");
    //countdown reaches 0, go to game over
    /*
    if(g.countdown==0){
        g.inContinue = false;
        g.inEndMenu = true;
    }
    */
    glPopMatrix();
    x11.swapBuffers();
}

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

bool timerCountdown(int timeTaken) {
    static int start_time = 1;
    if (start_time == 1) {
        start_time = time(NULL);
    }
    
    int elapsed = time(NULL) - start_time;
    //cout << elapsed << endl;

    if (elapsed >= timeTaken) {
        //cout << elapsed << endl;
        elapsed = 0;
        start_time = 1; // Reset the timer
        return true;  // 3 seconds have passed
    }
    return false;
}
