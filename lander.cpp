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
#include "classesLander.h"
#include "jalejo.h"
#include "jpocasangre.h"
#include <vector>
#include "jacosta.h"
#include "fonts.h"
#include "log.h"
#include <chrono>
#include <thread>
/*
Global g;
Lz1 lz1;
Lz2 lz2;
Lz3 lz3;
Lz4 lz4;
Lz5 lz5;
Lander lander;
X11_wrapper x11;
*/
FailureIndicator failureIndicator;
//---Justin's extern and function declarations---//
Lz lz;
Music music;
UFO myUFO;
Global g;
Lander lander;
Lander lander2;
vector<Asteroid> asteroids;
vector<X11steroid> X11steroids;
Bashteroid bashteroid;
Laser ufoLaser;
AlienHead alien;
Star stars[100];
Star stagstars[100];
Star slowstars[100];
bool checkCollision(const Lander& spaceship, const std::vector<Asteroid>& asteroids);
bool checkCollisionX11steroid(const Lander& spaceship, const std::vector<X11steroid>& X11steroids);
bool checkCollisionBash(const Lander& spaceship, const Bashteroid bashteroid);
extern int mouse_move_timer(const bool get);
//----------------------------------//

//floating point random numbers
#define rnd() (float)rand() / (float)RAND_MAX

//gravity pulling the rocket straight down
const float GRAVITY = 0.055;

// class and x11 functions 

/*Global::Global() {
    lives = 3;
    xres = 400;
    yres = 600;
    failed_landing = 0;
    landed = 0;
    color_reset = 0;
    accptl_angle = 90;
    temp_velocity = 0.0;
    showBox = false;
    nxtlanderX1 = 200.0f; nxtlanderX2 = 117.0f; nxtlanderX3 = 140.0f; nxtlanderX4 = 160.0f; nxtlanderX5 = 180.0f;
    nxtlanderY1 = 600.0f; nxtlander2Y = 600.0f; nxtlander3Y = 600.0f; nxtlander4Y = 600.0f; nxtlander5Y = 600.0f;
    lb = 50.0f;
    ub = 350.0f;
}*/

//Global g;



// Definitions for Lander
Lander::Lander() {
    init();
}

void Lander::init() {
    pos[0] = 200.0f;
    pos[1] = g.yres - 200.0f;
    vel[0] = vel[1] = 0.0f;
    //3 vertices of triangle-shaped rocket lander
    verts[0][0] = -10.0f;
    verts[0][1] =   0.0f;
    verts[1][0] =   0.0f;
    verts[1][1] =  30.0f;
    verts[2][0] =  10.0f;
    verts[2][1] =   0.0f;

    windowVerts[0][0] = -5.0f; windowVerts[0][1] = 10.0f;
    windowVerts[1][0] = 0.0f; windowVerts[1][1] = 20.0f;
    windowVerts[2][0] = 5.0f; windowVerts[2][1] = 10.0f;
    angle = 0.0;
    thrust = 0.0f;
    g.failed_landing = 0;
    radius = 10.0f;
}






Display* X11_wrapper::getDisplay() const {
    return dpy;
}

Window X11_wrapper::getWindow() const {
    return win;
}


X11_wrapper::~X11_wrapper()
{
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);
}

X11_wrapper::X11_wrapper()
{
	GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	int w = g.xres, h = g.yres;
	dpy = XOpenDisplay(NULL);
	if (dpy == NULL) {
		cout << "\n\tcannot connect to X server\n" << endl;
		exit(EXIT_FAILURE);
	}
	Window root = DefaultRootWindow(dpy);
	XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
	if (vi == NULL) {
		cout << "\n\tno appropriate visual found\n" << endl;
		exit(EXIT_FAILURE);
	} 
	Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
	XSetWindowAttributes swa;
	swa.colormap = cmap;
	swa.event_mask =
		ExposureMask | KeyPressMask | KeyReleaseMask |
		ButtonPress | ButtonReleaseMask |
		PointerMotionMask |
		StructureNotifyMask | SubstructureNotifyMask;
	win = XCreateWindow(dpy, root, 0, 0, w, h, 0, vi->depth,
		InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
	set_title();
	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);
}

void X11_wrapper::set_title()
{
	//Set the window title bar.
	XMapWindow(dpy, win);
	XStoreName(dpy, win, "XO sPaCE LifE ++</3");
}

bool X11_wrapper::getXPending()
{
	//See if there are pending events.
	return XPending(dpy);
}

XEvent X11_wrapper::getXNextEvent()
{
	//Get a pending event.
	XEvent e;
	XNextEvent(dpy, &e);
	return e;
}

void X11_wrapper::swapBuffers()
{
	glXSwapBuffers(dpy, win);
}

void X11_wrapper::reshape_window(int width, int height)
{
	//window has been resized.
	g.xres = width;
	g.yres = height;
	//
	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	glOrtho(0, g.xres, 0, g.yres, -1, 1);
}

void X11_wrapper::check_resize(XEvent *e)
{
	//The ConfigureNotify is sent by the
	//server if the window is resized.
	if (e->type != ConfigureNotify)
		return;
	XConfigureEvent xce = e->xconfigure;
	if (xce.width != g.xres || xce.height != g.yres) {
		//Window size did change.
		reshape_window(xce.width, xce.height);
	}
}
//-----------------------------------------------------------------------------

void X11_wrapper::check_mouse(XEvent *e)
{
	static int savex = 0;
	static int savey = 0;

	// int timer = total_running_time(false);
	// cout << timer << endl;
	
	//Weed out non-mouse events
	if (e->type != ButtonRelease &&
		e->type != ButtonPress &&
		e->type != MotionNotify) {
		//This is not a mouse event that we care about.
		return;
	}
	//
	if (e->type == ButtonRelease) {
		return;
	}
	if (e->type == ButtonPress) {
		if (e->xbutton.button==1) {
			//Left button was pressed.
			//int y = g.yres - e->xbutton.y;
			return;
		}
		if (e->xbutton.button==3) {
			//Right button was pressed.
			return;
		}
	}

	if (e->type == MotionNotify) {
		//The mouse moved!
		if (savex != e->xbutton.x || savey != e->xbutton.y) {
			savex = e->xbutton.x;
			savey = e->xbutton.y;
			//Code placed here will execute whenever the mouse moves.
			
			//Justin's function for lab;
			mouse_move_timer(true);
			

		}
	}
}

int X11_wrapper::check_keys(XEvent *e)
{
	if (e->type != KeyPress && e->type != KeyRelease)
		return 0;
	int key = XLookupKeysym(&e->xkey, 0);
	if (e->type == KeyPress)
		g.keys[key] = 1;
	if (e->type == KeyRelease)
		g.keys[key] = 0;
	if (e->type == KeyPress) {
		switch (key) {
			case XK_r:
				//Key R was pressed
				lander.init();
				break;
			case XK_Escape:
				//Escape key was pressed
				return 1;
			case XK_s:
				g.showBox = !g.showBox;  // Toggle box visibility
            	break;
		}
	}
	return 0;
}
X11_wrapper x11;
// end of x11 function 

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
		float startY = g.yres;//rand() % g.yres;
		float startRadius = rand() % 20 + 10;
		float startSpeed = rand() % 4 + 1;
		asteroids.push_back(Asteroid(startX, startY, startRadius, startSpeed));
	}
	//---------------------------------------------------//
	//Main loop

	bool restartCondition = true; // bool for restarting when false it ends
	do {	//do while loop to keep the game going
    bool done = false;
    while (!done) {
		
        //Process external events.
        while (x11.getXPending()) {
            XEvent e = x11.getXNextEvent();
            x11.check_resize(&e);
            x11.check_mouse(&e);
            done = x11.check_keys(&e);
        }
        // logic for game menu
        if (!inMenu) {
            physics();
            render();
			usleep(25000);
            x11.swapBuffers();
           if (g.failed_landing == 1) {
               g.failed_landing = 0;  
				this_thread::sleep_for(chrono::seconds(1));
                endMenu();
				lander.init();
            }
        } else {  
			//if inMenu true display and turn inMenu false
            handleMenu();
            inMenu = false;
        }
    }
} while (restartCondition);

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
	//----Initialize Stars-------//
	init_stars();
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
		lander.thrust = 0.1;

	}
	if (g.keys[XK_Left])
		lander.angle += 1.5;
	if (g.keys[XK_Right])
		lander.angle -= 1.5;



//handle_landerInter();

countPhysics(false); //function to count physics
//Justins physics functions------------------
moveLz();
ufoLaser.move();
moveBashteroid();
asteroidPhysics();
//--------------------------------------------
}
void render()
{

	glClear(GL_COLOR_BUFFER_BIT);

	/*to print out how many times physics is called
	commented out until we have everyones stats
	and box rendered together*/
    if(g.showBox){
	    //draw a gray box 
	    glColor3ub(100,100,100);
	    glPushMatrix();
	    glTranslatef(20.0, 20.0, 0.0);
	    int w = 230;
	    int h = 130;

	    glBegin(GL_QUADS);
		    glVertex2f(0, 0);
		    glVertex2f(0, h);
		    glVertex2f(w, h);
		    glVertex2f(w, 0);
	    glEnd();
	    glPopMatrix();
	    Rect r;
	    r.bot = 124;
	    r.left = 28;
	    r.center = 0;

	    ggprint13(&r, 20, 0x0055ff55, "Statistics... ");
	    ggprint13(&r, 20, 0x00ffff00, "physics called: %i", countPhysics(true));
	    ggprint13(&r, 20, 0x00ffff00, "sec since mouse move: %i", mouse_move_timer(false));
	    ggprint13(&r, 20, 0x00ffff00, "total run time: %i", total_running_time(true));
}

	//int timer = mouse_move_timer(false); Justin's timer for lab

	// Jacobs ggprint for lab
	// Justins ggprint for lab
	//ggprint13(&r, 20, 0x0055ff55, "Seconds since mouse moved: %i", timer);

	//justins render functions
	renderAsteroids();
	renderBashteroid();
	//moveAsteroids();
	render_stars();
	render_stagstars();
	render_slowstars();

	//Draw LZ
	glPushMatrix();
    //glColor3ub(250, 250, 20);
    glColor3ub(173, 216, 230);
    glTranslatef(lz.pos[0], lz.pos[1], 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-lz.width, -lz.height);
    glVertex2f(-lz.width,  lz.height);
    glVertex2f( lz.width,  lz.height);
    glVertex2f( lz.width, -lz.height);
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
		glColor3ub(100, 0, 100);
		glVertex2f(0.0+rnd()*14.0-7.0,
				lander.thrust * (-500.0 - rnd() * 500.0));
	}
	glEnd();
}
if (g.failed_landing) {
	//show crash graphics here...

}
glPopMatrix();

if (g.failed_landing) {
    glColor3ub(250, 0, 0); 
    failureIndicator.drawExplosion(lander.pos[0], lander.pos[1]);
}

if (g.failed_landing && !failureIndicator.isExploding) {
    failureIndicator.isExploding = true;
    failureIndicator.explosionRadii = {5.0f, 10.0f, 15.0f}; // Initial radii for circles
}

if (failureIndicator.isExploding) {
    for (float &radius : failureIndicator.explosionRadii) {
        radius += 1.0f; 
}

}
}






