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
	Display* getDisplay() const;
    Window getWindow() const;
	~X11_wrapper();
	X11_wrapper();
	void set_title();
	bool getXPending();
	XEvent getXNextEvent();
	void swapBuffers();
	void reshape_window(int width, int height);
	void check_resize(XEvent *e);
	void check_mouse(XEvent *e);
	int check_keys(XEvent *e);
};

extern X11_wrapper x11;

#endif
