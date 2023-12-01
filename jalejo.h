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

extern void moveBashteroid();
extern void asteroidPhysics();
extern void X11steroidPhysics();
extern void renderAsteroids();
extern void renderBashteroid();
extern void renderX11steroid();
extern void init_asteroids();
extern void reset_asteroids();

#endif