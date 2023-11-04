#ifndef _CLASSESLANDER_H
#define _CLASSESLANDER_H

#include <iostream>

/*class Global {
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
};*/

//extern Global g;
class Global {
    public:
        int xres, yres, zres;
        unsigned int keys[65536];
        int failed_landing;
        float color;
        int purp;
        int inversepurp;
        bool isDecreasing;
        bool inRange;
        bool starsmoveback;
        bool previousCollisionState;
        float collisionTime;
        bool resizeFlag;
        int targetXres;
        int targetYres;
        bool showBox;
        int menuChoice;
        bool inMenu;
        bool inEndMenu;
    
        Global() {
            xres = 400;
            yres = 600;
            failed_landing = 0;
            color = 1.0f;
            purp = 100;
            inversepurp = 0;
            isDecreasing = true;
            inRange = true;
            starsmoveback = false;
            previousCollisionState = false;
            collisionTime = 0;
            resizeFlag = false;
            showBox = false;
            menuChoice = 0;
            inMenu = true;
            inEndMenu = false;
        }
};
extern Global g;

class Lander 
{
    //the rocket
    public:
        float radius;
        float pos[2];
        float vel[2];
        float verts[3][2];
        float windowVerts[3][2];
        float thrust;
        double angle;
        float prevPos[2];
        Lander();
        void init();
};
extern Lander lander;
extern Lander lander2;

class Lz {
    public:
    float pos[2];
    float width;
    float height;
    Lz();
    void move(); 
    void moveback();
};
extern Lz lz;

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
