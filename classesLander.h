#ifndef _CLASSESLANDER_H
#define _CLASSESLANDER_H

using namespace std;
#include <iostream>

class Global {
    public:
        int lives = 3;
        int xres, yres;
        unsigned int keys[65536];
        int failed_landing;
        int landed;
        bool detach;
        int color_reset;
        int shiptrackX[2];
        double accptl_angle;
        double temp_velocity;

        int nxtlanderX1 = 200.0f;
        int nxtlanderX2 = 117.0f;
        int nxtlanderX3 = 140.0f;
        int nxtlanderX4 = 160.0f;
        int nxtlanderX5 = 180.0f;
 
        int nxtlanderY1 = 600.0f;
        int nxtlander2Y = 600.0f;
        int nxtlander3Y = 600.0f;
        int nxtlander4Y = 600.0f;
        int nxtlander5Y = 600.0f;

        int newXcoord1;
        int newXcoord2;
        int newXcoord3;
        int newXcoord4;
        int newXcoord5;


        int lb = 50.0f;
        int ub = 350.0f;
        Global() {
            xres = 400;
            yres = 600;
            failed_landing = 0;
            landed = 0;
            color_reset = 0;
            accptl_angle = 90;
            temp_velocity = 0.0;
        }
};

 extern Global g;

class Lz1 {
    //landing zone
    public:
        float pos[2];
        float width;
        float height;
        Lz1() { // Landing zone
            pos[0] = 200.0f; //X axis of platform
            pos[1] = 350.0f; //Y axis of platform
            width =  50.0f;
            height =  10.0f;
        }
}; 

extern Lz1 lz1;

class Lz2 {
    //landing zone
    public:
        float pos[2];
        float width;
        float height;
        Lz2() { // Landing zone
            pos[0] = 117.0f; //X axis of platform
            pos[1] = 1000.0f; //Y axis of platform
            width =  50.0f;
            height =  10.0f;
        }
}; 

extern Lz2 lz2;

class Lz3 {
    //landing zone
    public:
        float pos[2];
        float width;
        float height;
        Lz3() { // Landing zone
            pos[0] = 117.0f; //X axis of platform
            pos[1] = 1100.0f; //Y axis of platform
            width =  50.0f;
            height =  10.0f;
        }
}; 

extern Lz3 lz3;

class Lz4 {
    //landing zone
    public:
        float pos[2];
        float width;
        float height;
        Lz4() { // Landing zone
            pos[0] = 117.0f; //X axis of platform
            pos[1] = 1200.0f; //Y axis of platform
            width =  50.0f;
            height =  10.0f;
        }
}; 

extern Lz4 lz4;

class Lz5 {
    //landing zone
    public:
        float pos[2];
        float width;
        float height;
        Lz5() { // Landing zone
            pos[0] = 117.0f; //X axis of platform
            pos[1] = 1300.0f; //Y axis of platform
            width =  50.0f;
            height =  10.0f;
        }
}; 

extern Lz5 lz5;


class Lander {
    //the rocket
    public:
	float radius;
        float pos[2];
        float vel[2];
        float verts[3][2];
        float thrust;
        double angle;
        Lander() {
            init();
        }
        void init() {
            pos[0] = 200.0f;
            pos[1] = g.yres - 60.0f;

//#define TESTING
//#ifdef TESTING
            //pos[0] = 200.0f; //X axis of ship
            //pos[1] = 400.0f; //Y axis of ship
//#endif

            vel[0] = vel[1] = 0.0f;
            //3 vertices of triangle-shaped rocket lander
            verts[0][0] = -10.0f;
            verts[0][1] =   0.0f;
            verts[1][0] =   0.0f;
            verts[1][1] =  30.0f;
            verts[2][0] =  10.0f;
            verts[2][1] =   0.0f;
            angle = 0.0;
            thrust = 0.0f;
            g.failed_landing = 0;
	    //-Justin Adding raduis for collision detection
	    radius = 10.0f;
        }
}; 

extern Lander lander;

class X11_wrapper {
	private:
		Display *dpy;
		Window win;
		GLXContext glc;
	public:
    Display* getDisplay() const { return dpy; }
    Window getWindow() const { return win; }
    ~X11_wrapper()
{
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);
}

X11_wrapper()
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

void set_title()
{
	//Set the window title bar.
	XMapWindow(dpy, win);
	XStoreName(dpy, win, "Independence Month");
}

bool getXPending()
{
	//See if there are pending events.
	return XPending(dpy);
}

XEvent getXNextEvent()
{
	//Get a pending event.
	XEvent e;
	XNextEvent(dpy, &e);
	return e;
}

void swapBuffers()
{
	glXSwapBuffers(dpy, win);
}

void reshape_window(int width, int height)
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

void check_resize(XEvent *e)
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

void check_mouse(XEvent *e)
{
	static int savex = 0;
	static int savey = 0;

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
		}
	}
}

int check_keys(XEvent *e)
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
			//case XK_r:
				//Key R was pressed
				//g.color_reset = 1;

				//lander.init();
				//break;
			case XK_Escape:
				//Escape key was pressed
				return 1;
			case XK_space:
				//Space bar was pressed
				if (g.landed == true) {
					g.detach = true;
				}
				break;
			case XK_Up:
				//Up key was pressed
				if (g.landed == true) {
					g.detach = true;
				}
				break;

		}
	}
	return 0;
}
};

extern X11_wrapper x11;


#endif
