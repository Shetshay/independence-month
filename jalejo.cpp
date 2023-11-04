//Author: Justin Alejo
//created on september 27, 2023
#include <GL/glx.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <iostream>
#include "jalejo.h"
#include "classesLander.h"
#include <vector>
using namespace std;
//extern declarations



#define rnd() (float)rand() / (float)RAND_MAX

const int NUM_STARS = 100;

int mouse_move_timer(const bool get) 
{
	static int firsttime = 1;
	static int start_time;
	if (firsttime) {
		start_time = time(NULL);
		firsttime = 0;
	}
	
	if (get) {
		firsttime = 1;
		return start_time - start_time;
	}
	return time(NULL)-start_time;
}


//----Asteroid executables-----------------
Asteroid::Asteroid(float startX, float startY, float startRadius, float startSpeed)
{
    x = startX;
    y = startY;
    radius = startRadius;
    speed = startSpeed;
}

void Asteroid::move() 
{
    y -= speed;
    if (y < -radius) {
        reset();
    }
}

void Asteroid::moveback() 
{
    y += speed;
    if (y > g.yres) {
        reversereset();
    }
}

void Asteroid::reset()
{
    x = rand() % g.xres;
    y = g.yres + radius;
}

void Asteroid:: reversereset()
{
    x = rand() % g.xres;
    y = 0 - radius;
}

//-----------------------------------------

//--------X11steroid executables-----------
X11steroid::X11steroid(float startX, float startY, float startRadius, float startSpeed)
{
    x = startX;
    y = startY;
    radius = startRadius;
    speed = startSpeed;
}

void X11steroid::move() 
{
    y -= speed;
    if (y < -radius) {
        reset();
    }
}

void X11steroid::moveback() 
{
    y += speed;
    if (y > g.yres) {
        reversereset();
    }
}

void X11steroid::reset()
{
    x = rand() % g.xres;
    y = g.yres + radius;
}

void X11steroid:: reversereset()
{
    x = rand() % g.xres;
    y = 0 - radius;
}
//-----------------------------------------

//--------Bashteroid executables-----------
Bashteroid::Bashteroid() 
{
    x = rand() % g.xres;
    y = rand() % g.yres;
    radius = rand() % 20 + 10;
    speed = rand() % 3 + 1;
}

Bashteroid::Bashteroid(float startX, float startY, float startRadius, float startSpeed) 
{
    x = startX;
    y = startY;
    radius = startRadius;
    speed = startSpeed;
}

void Bashteroid::move() 
{
    y -= speed;
    if (y < -radius) {
        reset();
    }
}
        
void Bashteroid::reset() 
{
    x = rand() % g.xres;
    y = g.yres + radius;
}

void Bashteroid::moveback() 
{
    y += speed;
    if (y > g.yres) {
        reversereset();
    }
}
       
void Bashteroid::reversereset() {
    x = rand() % g.xres;
    y = 0 - radius;
}
        
//-----------------------------------------

//-----Class Lander executables------------
/*Lander::Lander() 
{
    init();
}
void Lander::init() 
{
    pos[0] = 200.0f;
    pos[1] = g.yres - 60.0f;
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
    prevPos[0] = pos[0];
    prevPos[1] = pos[1];
}*/
//-----------------------------------------

//----------UFO executables----------------
UFO::UFO() 
{
    pos[0] = 200.0f;
    pos[1] = 50.0f;
    radiusTop = 50.0f;
    radiusBottom = 30.0f;
    heightBottom = 20.0f;
}
//----------------------------------------

//--------Laser executables---------------
Laser::Laser() {
    pos[0] = 0.0f;
    pos[1] = 0.0f;
    length = 20.0f;
    speed = 3.0f;
    active = false;
}

void Laser::fire(float startX, float startY) {
    pos[0] = startX;
    pos[1] = startY;
    active = true;
}

void Laser::move() {
    if (active) {
        pos[1] += speed; // Move the laser downward
    }
}

void Laser::render() {
    if (active) {

        float laserWidth = 5.0f; // Width of the laser rectangle

        glColor3f(0.8f, 0.0f, 0.5f); // Purple color for the laser

        glBegin(GL_QUADS);
        
        glVertex2f(pos[0] - laserWidth/2, pos[1]);
        glVertex2f(pos[0] + laserWidth/2, pos[1]);
        glVertex2f(pos[0] + laserWidth/2, pos[1] - length);
        glVertex2f(pos[0] - laserWidth/2, pos[1] - length);
        
        glEnd();
    }
}
//----------------------------------------


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

//----------------------------------------

//----------AlienHead executable----------
void AlienHead::drawCircle(float cx, float cy, float r, float color[3]) {
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);  // Center
    for (int ii = 0; ii <= 100; ii++) {
        float theta = 2.0f * 3.1415926f * float(ii) / 100.0f;
        float dx = r * cosf(theta);
        float dy = r * sinf(theta);
        glVertex2f(cx + dx, cy + dy);
    }
    glEnd();
}

void AlienHead::drawOval(float cx, float cy, float rx, float ry, float angle, float color[3]) {
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);  // Center
    for (int ii = 0; ii <= 100; ii++) {
        float theta = 2.0f * 3.1415926f * float(ii) / 100.0f;
        float dx = rx * cosf(theta);
        float dy = ry * sinf(theta);
        
        float rotatedX = cx + (dx * cosf(angle) - dy * sinf(angle));
        float rotatedY = cy + (dx * sinf(angle) + dy * cosf(angle));
        
        glVertex2f(rotatedX, rotatedY);
    }
    glEnd();
}

void AlienHead::alienrender(float cx, float cy) {
    float headColor[3] = {0.2f, 0.9f, 0.2f};  // Yellowish color for the alien head
    float eyeColor[3] = {1.0f, 0.0f, 0.0f};   // Red color for the eyes

    // Draw the head
    drawCircle(cx, cy, 15.0f, headColor);

    // Draw the left eye as a tilted oval
    drawOval(cx - 8.0f, cy + 2.0f, 3.0f, 5.0f, 0.3f, eyeColor);

    // Draw the right eye as a tilted oval
    drawOval(cx + 8.0f, cy + 2.0f, 3.0f, 5.0f, -0.3f, eyeColor);
}
//----------------------------------------
void init_stars() 
{ 
    srand(time(NULL));
    for (int i = 0; i < NUM_STARS; i++) {
        float x = static_cast<float>(rand() % g.xres);
        float y = static_cast<float>(rand() % g.yres);
        stars[i] = Star(x, y);
    }
    for (int i = 0; i < 100; i++) {
        float x = static_cast<float>(rand() % g.xres);
        float y = static_cast<float>(rand() % g.yres);
        stagstars[i] = Star(x,y);
    }
    for (int i = 0; i < 100; i++) {
        float x = static_cast<float>(rand() % g.xres);
        float y = static_cast<float>(rand() % g.yres);
        slowstars[i] = Star(x,y);
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

void render_stars(){

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    for(int i = 0; i < NUM_STARS; i++){

        glVertex2f(stars[i].x, stars[i].y);
    }
    glEnd();
}

void render_stagstars(){
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    for(int i = 0; i < NUM_STARS; i++){

        glVertex2f(stagstars[i].x, stagstars[i].y);
    }
    glEnd();
}

void render_slowstars(){
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    for(int i = 0; i < 100; i++){

        glVertex2f(slowstars[i].x, slowstars[i].y);
    }
    glEnd();
}

bool checkCollisionBash(const Lander& spaceship, const Bashteroid bashteroid) {
   
        float distance = sqrt(pow(spaceship.pos[0] - bashteroid.x, 2) + pow(spaceship.pos[1] - bashteroid.y, 2));

        if (distance < (spaceship.radius + bashteroid.radius))
            return true;
    
    return false;
}

void renderBashteroid() {
    glColor3f(1.0f, 0.5f, 1.0f);
    

        glPushMatrix();
        glTranslatef(bashteroid.x, bashteroid.y, 0.0f);
        glLineWidth(5.0f);
        glBegin(GL_LINES);
        for (int i = 0; i < 35; i++) {
        /*glColor3f(0.7f,0.0f,0.7f);
        glVertex2f((rnd() * bashteroid.radius * 2) - bashteroid.radius, 0.0);
        glColor3f(1.0f, 0.5f, 1.0f);
        glVertex2f(0.0 + rnd() * 14.0-7.0, (50.0 + rnd() * 50.0));*/
        // Define the start (purple) and end (blue) colors for the gradient
float startColor[3] = {0.5f, 0.0f, 0.5f}; // Purple
float endColor[3] = {0.0f, 0.0f, 1.0f};   // Blue

// Interpolate between the start and end colors based on the y position of the vertex
float a = (rnd() * bashteroid.radius * 2 - bashteroid.radius) / (2.0f * bashteroid.radius); 
glColor3f((1 - a) * startColor[0] + a * endColor[0], 
          (1 - a) * startColor[1] + a * endColor[1], 
          (1 - a) * startColor[2] + a * endColor[2]);
glVertex2f((rnd() * bashteroid.radius * 2) - bashteroid.radius, 0.0);

float b = (50.0 + rnd() * 50.0) / 100.0;
glColor3f((1 - b) * startColor[0] + b * endColor[0], 
          (1 - b) * startColor[1] + b * endColor[1], 
          (1 - b) * startColor[2] + b * endColor[2]);
glVertex2f(0.0 + rnd() * 14.0 - 7.0, (50.0 + rnd() * 50.0));

//glEnd();
        }
        glEnd();

            glBegin(GL_TRIANGLE_FAN);
            for(int i= 0; i < 360; i +=15) {

                float angle = i * 3.14159265f / 180.0f;
                float x = bashteroid.radius * cos(angle);
                float y = bashteroid.radius * sin(angle);
                glVertex2f(x,y);
                float t = static_cast<float>(i) / 360.0f;
                
                
                float red = (1.0f - t) * 0.5f;
                float green = 0.0f;
                float blue = t + 0.5f * (1.0f - t);

                glColor3f(red, green, blue);
                glVertex2f(x, y);
            }
            glEnd();
            glPopMatrix();
    
}

void renderAsteroids() {

    glColor3f(1.0f, 1.0f, 1.0f);
    for(const Asteroid& asteroid : asteroids) {

        glPushMatrix();
        glTranslatef(asteroid.x, asteroid.y, 0.0f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
            for(int i = 0; i < 35; i++) {

                glColor3ub(255,0,0);
                glVertex2f((rnd() * asteroid.radius * 2) - asteroid.radius, 0.0);
                glColor3ub(250, 250, 0);
                glVertex2f(0.0 + rnd() * 14.0-7.0, (50.0 + rnd() * 50.0));
            }
            glEnd();

            glBegin(GL_TRIANGLE_FAN);
            for(int i= 0; i < 360; i +=15) {

                float angle = i * 3.14159265f / 180.0f;
                float x = asteroid.radius * cos(angle);
                float y = asteroid.radius * sin(angle);
                glVertex2f(x,y);
                float t = static_cast<float>(i) / 360.0f;
                
                
                float red = 1.0f;
                float green = t;

                glColor3f(red, green, 0.0f);
                glVertex2f(x, y);
            }
            glEnd();
            glPopMatrix();
    }
}

void renderX11steroid() {

    glColor3f(1.0f, 1.0f, 1.0f);
    for(const X11steroid& X11steroid : X11steroids) {

        glPushMatrix();
        glTranslatef(X11steroid.x, X11steroid.y, 0.0f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
            for(int i = 0; i < 35; i++) {

                glColor3ub(0,0,0);
                glVertex2f((rnd() * X11steroid.radius * 2) - X11steroid.radius, 0.0);
                glColor3ub(50, 50, 50);
                glVertex2f(0.0 + rnd() * 14.0-7.0, (50.0 + rnd() * 50.0));
            }
            glEnd();

            glBegin(GL_TRIANGLE_FAN);
            for(int i= 0; i < 360; i +=15) {

                float angle = i * 3.14159265f / 180.0f;
                float x = X11steroid.radius * cos(angle);
                float y = X11steroid.radius * sin(angle);
                glVertex2f(x,y);
                float t = static_cast<float>(i) / 360.0f;
                
                
                float grayShade = 0.3f * (1.0f + sin(t * 3.14159265f));

                glColor3f(grayShade, grayShade, grayShade);
                glVertex2f(x, y);
            }
            glEnd();
            glPopMatrix();
    }
}

/*void music_effects() {

    if(g.starsmoveback && !music.eventOccurred) {
        if(music.musicbgMusicPlaying) {
            alSourcePause(alSource);
            music.bgMusicPlaying = false;
        }
        if(!music.eventSoundPlaying) {
            alSourcePlay(eventSource);
            eventSoundPlaying = true;
        }
        eventOccurred = true;
    }
    else if(!g.starsmoveback && music.eventOccurred) {
        if(music.eventSoundPlaying) {
            alSourceStop(eventSource);
            music.eventSoundPlaying = false;
        }
        if(!music.bgMusicPlaying) {
            alSourcePlay(alSource)
            music.bgMusicPlaying = true;
        }
        eventOccured = false;
    }
}*/

bool checkCollision(const Lander& spaceship, const std::vector<Asteroid>& asteroids) {

    for(const Asteroid& asteroid : asteroids) {
        float distance = sqrt(pow(spaceship.pos[0] - asteroid.x, 2) + pow(spaceship.pos[1] - asteroid.y, 2));

        if (distance < (spaceship.radius + asteroid.radius))
            return true;
    }

    return false;

}

bool checkCollisionX11steroid(const Lander& spaceship, const std::vector<X11steroid>& X11steroids) {

    for(const X11steroid& X11steroid : X11steroids) {
        float distance = sqrt(pow(spaceship.pos[0] - X11steroid.x, 2) + pow(spaceship.pos[1] - X11steroid.y, 2));

        if (distance < (spaceship.radius + X11steroid.radius))
            return true;
    }

    return false;

}

/*void X11steroidPhysics() 
{
    if (checkCollisionX11steroid(lander, X11steroids)) {
        //cout << "Spaceship collided with an asteroid!" << endl;
        //g.failed_landing = 1;
        g.xres -= 1;
        g.yres -= 1;
        x11.reshape_window(g.xres, g.yres);
    }
    if(g.starsmoveback) {
        for (X11steroid& X11steroid : X11steroids) {
            X11steroid.moveback();
        }
    } else {
        for (X11steroid& X11steroid : X11steroids) {
            X11steroid.move();
        }
    }
}*/

/*void Resize() 
{
    x11.reshape_window(350, 550);
}*/


void asteroidPhysics() 
{
    if (checkCollision(lander, asteroids)) {
        //cout << "Spaceship collided with an asteroid!" << endl;
        g.failed_landing = 1;
    }
    if(g.starsmoveback) {
        for (Asteroid& asteroid : asteroids) {
            asteroid.moveback();
        }
    } else {
        for (Asteroid& asteroid : asteroids) {
            asteroid.move();
        }
    }
}

void move_stars() {
    if (g.starsmoveback) {
        for(int j = 0; j < 100; j++) {
            stars[j].y += 1.0f;
            //stars[j].x += 1.0f;
            slowstars[j].y += 0.5f;
            //slowstars[j].x -= 0.5f;
            stagstars[j].y += 0.25f;
            if(stars[j].y > g.yres)
                stars[j].y = 0;
            if(slowstars[j].y > g.yres)
                slowstars[j].y = 0;
            if(stagstars[j].y > g.yres)
                stagstars[j].y = 0;
            /*if(stars[j].x > g.xres)
                stars[j].x = 0;
            if(slowstars[j].x < 0)
            slowstars[j].x = g.xres;*/
        }

    } 
    else {
        
        for(int j = 0; j < 100; j++) {
            stars[j].y -= 1.0f;
            if(stars[j].y < 0)
            stars[j].y = g.yres;
        }
        
        for(int j = 0; j < 100; j++) {
            slowstars[j].y -= 0.5f;
            if(slowstars[j].y < 0)
            slowstars[j].y = g.yres;
        }
        for(int j = 0; j < 100; j++) {
            stagstars[j].y -= 0.25f;
            if(stagstars[j].y < 0)
            stagstars[j].y = g.yres;
    }
    }
}


void moveBashteroid() 
{
    bool currentCollisionState = checkCollisionBash(lander, bashteroid);

    if (currentCollisionState && !g.previousCollisionState) {
        g.starsmoveback = !g.starsmoveback;
    }
    
    g.previousCollisionState = currentCollisionState;
    
    if (g.starsmoveback) {
        bashteroid.moveback();
    } else {
        bashteroid.move();
    }

    move_stars();

}

void moveLz() 
{
    if(g.starsmoveback) {
        lz.moveback();
    } else {
        lz.move();
    }
}

void shootlaser() 
{
    if(g.starsmoveback) {
        //Do nothing
    } else {
        if(myUFO.pos[0] < lander.pos[0] + 5 && myUFO.pos[0] > lander.pos[0] - 5) {
        ufoLaser.fire(myUFO.pos[0], myUFO.pos[1] - myUFO.radiusBottom);
        }
    }
}

