// modified by group 2 // andrew, justin, gus, john, jacob
// 12/3/2023

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
#include "gjimenez3.h"
#include "classesLander.h"
#include "jalejo.h"
#include "jpocasangre.h"
#include <vector>
#include "jacosta.h"
#include "fonts.h"
#include "log.h"
//#include "highscore.h"
#include <chrono>
#include <thread>
#include <fcntl.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#ifdef USE_OPENAL_SOUND
#include </usr/include/AL/alut.h>
#endif //USE_OPENAL_SOUND

FailureIndicator failureIndicator;
FailureIndicator2 secondaryIndicator;
Record record;
UFO myUFO;
AlienHead alien;
Laser ufoLaser;

//---Justin's extern and function declarations---//
Lz lz;
Music music;
Global g;
Lander lander;
Lander lander2;
vector<Asteroid> asteroids;
vector<X11steroid> X11steroids;
vector<Bashteroid> bashteroids;
Star stars[100];
Star stagstars[100];
Star slowstars[100];
Star acidstars[100];
Star acidslowstars[100];
Star acidstagstars[100];
bool checkCollision(const Lander& spaceship, const Lander& spaceship2, const std::vector<Asteroid>& asteroids);
bool checkCollisionX11steroid(const Lander& spaceship, const Lander& spaceship2, const std::vector<X11steroid>& X11steroids);
bool checkCollisionBash(const Lander& spaceship, const Lander& spaceship2, const std::vector<Bashteroid>& bashteroids);
extern int mouse_move_timer(const bool get);

//----------------------------------//
void renderPauseScreen();
void renderContinueScreen();
//
//Andrew's extern---------
void askForName(std::string& playerName);
//------------------------

//floating point random numbers
#define rnd() (float)rand() / (float)RAND_MAX

//gravity pulling the rocket straight down
const float GRAVITY = 0.055;

// class and x11 functions 

//ignore this --Justin----
void testCircle(float centerX, float centerY, float radius) 
{
    int segments = 100; // More segments = smoother circle
    float angleStep = 2.0f * M_PI / segments;

    // Set color to red
    glColor3f(1.0f, 0.0f, 0.0f);

    // Start drawing the circle
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < segments; i++) {
        float angle = angleStep * i;
        float x = centerX + cos(angle) * radius;
        float y = centerY + sin(angle) * radius;
        glVertex2f(x, y);
    }

    glEnd();
}

// Definitions for Lander
Lander::Lander() 
{
	init();
}

void Lander::init() 
{
	pos[0] = 200.0f;
    pos[1] = g.yres - 300.0f;
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

void Lander::init2() 
{
    pos[0] = 150.0f;
    pos[1] = g.yres - 300.0f;
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


Display* X11_wrapper::getDisplay() const 
{
    return dpy;
}

Window X11_wrapper::getWindow() const 
{
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
	XResizeWindow(dpy, win, width, height);
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
			record.setEnd(savex, savey);
            //cout << "Mouse traveled: " << record.getDistance() << " pixels." << endl;
            record.setStart(savex, savey);

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
		if (g.inContinue) {
    		if (key == XK_c) {
        		g.yesContinue = true;
    		} else if (key == XK_m) {
        		g.inContinue = false;
        		g.inMenu = true;
				g.inEndMenu = false;
    		}
		}
		switch (key) {
			case XK_r:
				//Key R was pressed
				lander.init();
				break;
			case XK_Escape:
				//Escape key was pressed
				return 1;
			case XK_p:
				g.paused = !g.paused;
				break;
			case XK_s:
				g.showBox = !g.showBox;  // Toggle box visibility
            	break;
			case XK_q:
				g.inscoreMenu = !g.inscoreMenu;
				break;
			case XK_Return: // 'Enter' key to select menu option
            if (g.inMenu) {
				if (g.menuChoice == 0) {
                    // Start the game
					askForName(g.playerName);
					g.setPlayerName(g.playerName);
					g.inMenu = false;
					lander.init();
					reset_asteroids();
					g.twoPlayer = false;
					//Reset Alien Laser
                } else if (g.menuChoice == 1) {
                    // Activates two Player
					g.twoPlayer = true;
					g.inMenu = false;
					lander.init();
					lander2.init2();
					reset_asteroids();
                } else if (g.menuChoice == 2) {
					g.inscoreMenu = !g.inscoreMenu;
                } else if (g.menuChoice == 3) {
                    // Quit the game
                    exit(0);
                }
				} else if (g.inEndMenu) {
                    if (g.menuChoice == 0) {
                        /* Back to Main Menu
                        g.inEndMenu = false;
						if(g.twoPlayer) {
							//init_asteroids();
							reset_asteroids();
                        	lander.init();
							lander2.init2();
						} else {
							lander.init();
							reset_asteroids();
							//init_asteroids();
						}
						*/
						g.inMenu = true;
						g.inEndMenu = false;
						g.paused = false;
					
                    } else if (g.menuChoice == 1) {
                        //check scores(need to still work on)
						g.inscoreMenu = !g.inscoreMenu;
                        
                    } else if (g.menuChoice == 2) {
                        // Quit the game
                        exit(0);
                    }
				
                }
                break;
                
            case XK_Up: // Up arrow key
                g.menuChoice = (g.menuChoice + 2) % 3;
                break;
            case XK_Down: // Down arrow key
                g.menuChoice = (g.menuChoice + 1) % 4;
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
	//bool for menu handling
	logOpen();
	init_opengl();
	printf("Press T or Up-arrow for thrust.\n");
	printf("Press Left or Right arrows for rocket thrust vector.\n");
	//Justin--initializing asteroids--
	init_asteroids();
	init_stars();
	//Main loop

	#ifdef USE_OPENAL_SOUND
	alutInit(0, NULL);
	    if(alGetError() != AL_NO_ERROR) {
        printf("ERROR: aluINIT()\n");
        return 0;
    }
    alGetError();
    float vec[6] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alListenerfv(AL_ORIENTATION, vec);
    alListenerf(AL_GAIN, 1.0f);
    //--------------
    ALuint eventBuffer, eventSource;
    eventBuffer = alutCreateBufferFromFile("reversed.wav");
    alGenSources(1, &eventSource);
    alSourcei(eventSource, AL_BUFFER, eventBuffer);
    alSourcef(eventSource, AL_GAIN, 1.0f);
    alSourcef(eventSource, AL_PITCH, 1.0f);
    alSourcei(eventSource, AL_LOOPING, AL_TRUE);
    //--------------
    ALuint alBuffer;
    alBuffer = alutCreateBufferFromFile("8bittourlife.wav");

    ALuint alSource;
    alGenSources(1, &alSource);
    alSourcei(alSource, AL_BUFFER, alBuffer);
    alSourcef(alSource, AL_GAIN, 1.0f);
    alSourcef(alSource, AL_PITCH, 1.0f);
    alSourcei(alSource, AL_LOOPING, AL_TRUE);
    if (alGetError() != AL_NO_ERROR) {
        printf("ERROR: setting source \n");
        return 0;
    }
    alSourcePlay(alSource);

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
        if (!g.inMenu && !g.inEndMenu && !g.inContinue && !g.paused) {
            physics();
            render();

		if (g.starsmoveback && !music.eventOccurred) {
        	if (music.bgMusicPlaying) {
            	alSourcePause(alSource);
            	music.bgMusicPlaying = false;
        	}
        	if (!music.eventSoundPlaying) {
            	alSourcePlay(eventSource);
            	music.eventSoundPlaying = true;
        	}
        	music.eventOccurred = true;
    	}
		
		else if (!g.starsmoveback && music.eventOccurred) {
        	if (music.eventSoundPlaying) {
            	alSourceStop(eventSource);
            	music.eventSoundPlaying = false;
    		}
        	if (!music.bgMusicPlaying) {
            	alSourcePlay(alSource);
            	music.bgMusicPlaying = true;
        	}
        	music.eventOccurred = false;
    	}

			usleep(25000);
            x11.swapBuffers();
           if (g.failed_landing == 1) {
				g.menuChoice = 0;
				g.countdown = 10;
				//g.inContinue = true;
				g.yesContinue = false;

				glColor3ub(250, 0, 0); 
				failureIndicator.drawExplosion(lander.pos[0], lander.pos[1]);
				secondaryIndicator.drawFragments();  


				if (!failureIndicator.isExploding) {
    			failureIndicator.isExploding = true;
	    		failureIndicator.explosionRadii = {5.0f, 10.0f, 15.0f}; 
    			secondaryIndicator.createFragments(lander.pos[0], lander.pos[1], 200);
				}

				if (failureIndicator.isExploding) {
					failureIndicator.isExploding = true;
					secondaryIndicator.updateFragments();
				}

				if (failureIndicator.isExploding) {
					secondaryIndicator.drawFragments();
					for (float &radius : failureIndicator.explosionRadii) {
						radius += 150.0f; 
				}
				}
					sendHighScore(g.playerName, countHighscore(false));

				if(timer(3)){
					//g.inEndMenu = true;
					g.inContinue = true;
					g.failed_landing = 0;
					secondaryIndicator.reset();
					//Reset Alien Laser
					failureIndicator.isExploding = false;
					ufoLaser.reset();
					countHighscore(true);
				}	
		   }
        } else if (g.inMenu) {
				lander.init();
	      		reset_asteroids();	
			//if inMenu true display and turn inMenu false
			if (g.inscoreMenu) {
				displayHighScores();
			} else {
				handleMenu();
			}
		} else if (g.inContinue) {
			renderContinueScreen();
			//"c" is pressed/continue is chosen
			if (g.yesContinue) {
				if (g.twoPlayer == true) {
				g.failed_landing = 0;
				g.inContinue = false;
				secondaryIndicator.reset();
				failureIndicator.isExploding = false;
				lander.init();
				lander2.init2(); // Reinitialize game state or similar logic
				//Reset Alien Laser
				ufoLaser.reset();
				g.color = 1.0f;
				reset_asteroids();
				} else {
					g.failed_landing = 0;
					g.inContinue = false;
					secondaryIndicator.reset();
					failureIndicator.isExploding = false;
					lander.init();
					lander2.init2();
					//Reset Alien Laser
					ufoLaser.reset();
					g.color = 1.0f;
					reset_asteroids();
				}
			}
			if (g.countdown == 0) {
				g.inContinue = false;
        		g.inEndMenu = true;
			}
        	} else if (g.inEndMenu) {
			if (g.inscoreMenu) {
				displayHighScores();
			} else {
				//countHighscore(false);
				endMenu();
			}	
	} else if (g.paused == true) {
			renderPauseScreen();
    	}
		
    }
} while (restartCondition);

	cleanup_fonts();
	logClose();
	
	alSourceStop(alSource);
	alSourceStop(eventSource);
    alDeleteSources(1, &alSource);
	alDeleteSources(1, &eventSource);
    alDeleteBuffers(1, &alBuffer);
    alDeleteBuffers(1, &eventBuffer);
    ALCcontext *Context = alcGetCurrentContext();
    ALCdevice *Device = alcGetContextsDevice(Context);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(Context);
    alcCloseDevice(Device);
	alutExit();
    #endif //USE_OPENAL_SOUND
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
	//init_stars();
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

// two player mode bool
	if (g.twoPlayer) {
		lander2.pos[0] += lander2.vel[0];
		lander2.pos[1] += lander2.vel[1];
		lander2.vel[1] -= GRAVITY;


		//lz.pos[0] += 0.6f;

		//apply thrust
		//convert angle to radians...
		float ang = ((lander2.angle+90.0) / 360.0) * (3.14159 * 2.0);
		//make a thrust vector...
		float xthrust = cos(ang) * lander2.thrust;
		float ythrust = sin(ang) * lander2.thrust;
		lander2.vel[0] += xthrust;
		lander2.vel[1] += ythrust;
		lander2.thrust *= 0.95f;
		if (g.keys[XK_w]) {
			//Thrust for the rocket, and movement of stars
			lander2.thrust = 0.1;
		}
		if (g.keys[XK_a])
			lander2.angle += 1.5;
		if (g.keys[XK_d])
			lander2.angle -= 1.5;
	}

	countPhysics(false); //function to count physics
//Justins physics functions------------------
	moveLz();
	ufoLaser.move();
	shootlaser();
	moveBashteroid();
	asteroidPhysics();
	X11steroidPhysics();
//--------------------------------------------
	lander_boundaries();
	move_stars();
	move_ufo();

}

void render()
{

	glClear(GL_COLOR_BUFFER_BIT);
	
	render_space_color();
	render_stars();
	render_slowstars();
	render_stagstars();
	//print out score(will need to fix)
	Rect r;
    r.center = 0;
	r.bot = g.yres - 50;
    r.left = 10;

		ggprint13(&r, 20, 0x0055ff55, "HIGH SCORE IS: %i", countHighscore(false));
		//r.bot = 550;
    	ggprint13(&r, 20, 0x0055ff55, "Player: %s", g.playerName.c_str());
		g.tempHighscore = g.highscore;

	/*stats box from gordons lab*/
    if (g.showBox) {
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
	renderX11steroid();
	//AlienHead.alienrender();
	render_iceblock();
	ufoLaser.render();
	renderUFO(myUFO);

	glEnable(GL_BLEND);
	// makes the shrimp transparent
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 	Draw Lander
	glPushMatrix();
	glColor4f(1.0f, g.color, g.color, 1.0f);
	g.color -= 0.001f;
	if (g.color < 0) {
		g.failed_landing = 1;
	}
	if (g.failed_landing) {
    	// Color red
    	glColor3f(1.0f, 0.0f, 0.0f);
	}

	glTranslatef(lander.pos[0], lander.pos[1], 0.0f);
	glRotated(lander.angle, 0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLES);
	for (int i=0; i<3; i++) {
		glVertex2f(lander.verts[i][0], lander.verts[i][1]);
	}
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 3; i++) {
		glVertex2f(lander.windowVerts[i][0], lander.windowVerts[i][1]);
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
	glPopMatrix();

	if (g.twoPlayer) {
		glPushMatrix();
		glColor4f(1.0f, g.color, g.color, 1.0f);
		g.color -= 0.001f;
		if (g.color < 0) {
			g.failed_landing = 1;
		}
	
		if (g.failed_landing) {
			glColor3ub(250, 0, 0); //Red color USLEEP WHILE LOOP TO INDICATE LIFE LOST
		}

		glTranslatef(lander2.pos[0], lander2.pos[1], 0.0f);
		glRotated(lander2.angle, 0.0, 0.0, 1.0);
		glBegin(GL_TRIANGLES);
		for (int i=0; i<3; i++) {
			glVertex2f(lander2.verts[i][0], lander2.verts[i][1]);
		}
		glEnd();

		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < 3; i++) {
			glVertex2f(lander.windowVerts[i][0], lander.windowVerts[i][1]);
		}
		glEnd();
		//Lander thrust
		if (lander2.thrust > 0.0) {
		//draw the thrust vector
		glBegin(GL_LINES);
		for (int i=0; i<25; i++) {
			glColor3ub(0, 0, 255);
			glVertex2f(rnd()*10.0-5.0, 0.0);
			glColor3ub(100, 0, 100);
			glVertex2f(0.0+rnd()*14.0-7.0,
				lander2.thrust * (-500.0 - rnd() * 500.0));
		}
			glEnd();
		}
		glPopMatrix();
	}

	if (g.failed_landing) {
	//show crash graphics here...
	x11.reshape_window(400, 600);
	}
	

	if (g.failed_landing) {
		glColor3ub(250, 0, 0); 
		failureIndicator.drawExplosion(lander.pos[0], lander.pos[1]);
		//secondaryIndicator.createFragments(lander.pos[0], lander.pos[1], 50);
		secondaryIndicator.drawFragments();  
	}

	if (g.failed_landing && !failureIndicator.isExploding) {
    	failureIndicator.isExploding = true;
	    failureIndicator.explosionRadii = {5.0f, 10.0f, 15.0f}; 
    	secondaryIndicator.createFragments(lander.pos[0], lander.pos[1], 200);
	}

	if (failureIndicator.isExploding) {
		failureIndicator.isExploding = true;
    	secondaryIndicator.updateFragments();
	}

	if (failureIndicator.isExploding) {
    	secondaryIndicator.drawFragments(); 
		for (float &radius : failureIndicator.explosionRadii) {
        	radius += 150.0f; 
		}
	}
	//testCircle(lander.pos[0], lander.pos[1], lander.radius);
}








