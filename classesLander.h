#ifndef _CLASSESLANDER_H
#define _CLASSESLANDER_H

#include <iostream>

class Global {
public:
    int lives;
    int xres, yres;
    unsigned int keys[65536];
    int failed_landing;
    int landed;
    bool detach;
    int color_reset;
    int shiptrackX[2];
    double accptl_angle;
    double temp_velocity;
    bool showBox;
    int nxtlanderX1, nxtlanderX2, nxtlanderX3, nxtlanderX4, nxtlanderX5;
    int nxtlanderY1, nxtlander2Y, nxtlander3Y, nxtlander4Y, nxtlander5Y;
    int newXcoord1, newXcoord2, newXcoord3, newXcoord4, newXcoord5;
    int lb, ub;
    
    Global();
};

extern Global g;

class Lz1 {
public:
    float pos[2];
    float width;
    float height;
    Lz1();
};

extern Lz1 lz1;

class Lz2 {
public:
    float pos[2];
    float width;
    float height;
    Lz2();
};

extern Lz2 lz2;

class Lz3 {
public:
    float pos[2];
    float width;
    float height;
    Lz3();
};

extern Lz3 lz3;

class Lz4 {
public:
    float pos[2];
    float width;
    float height;
    Lz4();
};

extern Lz4 lz4;

class Lz5 {
public:
    float pos[2];
    float width;
    float height;
    Lz5();
};

extern Lz5 lz5;

class Lander {
public:
    float radius;
    float pos[2];
    float vel[2];
    float verts[3][2];
    float thrust;
    double angle;

    Lander();
    void init();
};

extern Lander lander;

class X11_wrapper {
public:
    X11_wrapper();
    ~X11_wrapper();

    Display* getDisplay() const;
    Window getWindow() const;
    void set_title();
    bool getXPending();
    XEvent getXNextEvent();
    void swapBuffers();
    void reshape_window(int width, int height);
    void check_resize(XEvent *e);
    void check_mouse(XEvent *e);
    int check_keys(XEvent *e);

private:
    Display *dpy;
    Window win;
    GLXContext glc;
};

extern X11_wrapper x11;

#endif
