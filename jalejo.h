//Author: Justin Alejo
//Created on 9/29/2023
#ifndef _JALEJO_H
#define _JALEJO_H

#include <iostream>
#include <vector>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
using namespace std;
#define rnd() (float)rand() / (float)RAND_MAX

/*class Global {
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
        }
};
extern Global g;*/

/*class Lander 
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
extern Lander lander2;*/

class UFO {
    public:
        float pos[2];       // Position of the UFO
        float radiusTop;    // Radius of the top disc
        float radiusBottom; // Radius of the bottom dome
        float heightBottom; // Height of the bottom dome

        UFO();
};
extern UFO myUFO;

class Laser {
public:
    float pos[2]; // Position [x, y]
    float length; // Length of the laser
    float speed;  // Speed of the laser movement
    bool active;  // Indicates if the laser is currently active or not

    Laser();
    void fire(float startX, float startY);
    void move();
    void render();
};
extern Laser ufoLaser;

class AlienHead {
public:
    void drawCircle(float cx, float cy, float r, float color[3]);
    void drawOval(float cx, float cy, float rx, float ry, float angle, float color[3]);
    void alienrender(float cx, float cy);
};
extern AlienHead alien;


/*class Lz {
    public:
    float pos[2];
    float width;
    float height;
    Lz();
    void move(); 
    void moveback();
};
extern Lz lz;*/

/*struct Star{
    float x, y;
    Star(){
        x = 0.0f;
        y = 0.0f;
    }
    Star(float ex, float why){
        x = ex;
        y = why;
    }
};

extern Star stars[100];
extern Star stagstars[100];
extern Star slowstars[100];*/


class Asteroid{
    public:
        float x, y;
        float radius;
        float speed;
        Asteroid(float startX, float startY, float startRadius, float startSpeed);
        void move();
        void moveback();
        void reset();
        void reversereset();
};

extern vector<Asteroid> asteroids;

class X11steroid{
    public:
        float x, y;
        float radius;
        float speed;
        X11steroid(float startX, float startY, float startRadius, float startSpeed);
        void move();
        void moveback();
        void reset();
        void reversereset();
};
extern vector<X11steroid> X11steroids;

class Bashteroid {
    public:
        float x, y;
        float radius;
        float speed;

        Bashteroid();
        Bashteroid(float startX, float startY, float startRadius, float startSpeed);
        void move();
        void moveback();
        void reset();
        void reversereset();
};
extern vector<Bashteroid> bashteroids;

class Music {
    public:
    bool bgMusicPlaying;
    bool eventSoundPlaying;
    bool eventOccurred;
    Music() {
        bgMusicPlaying = true;
        eventSoundPlaying = false;
        eventOccurred = false;
    }
};
extern Music music;

/*class X11_wrapper {
    private:
        Display *dpy;
        Window win;
        GLXContext glc;
    public:
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
};*/
//extern X11_wrapper x11;

extern void shootlaser();
//extern void moveLz();
//extern void change_value();
//extern void move_stars();
extern void moveBashteroid();
extern void asteroidPhysics();
extern void X11steroidPhysics();
//extern void render_stars();
//extern void render_stagstars();
//extern void render_slowstars();
//extern void init_stars();
extern void renderAsteroids();
extern void renderBashteroid();
extern void renderX11steroid();
extern void init_asteroids();

#endif