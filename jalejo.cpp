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
    radius = rand() % 20 + 10;
    speed = rand() % 3 + 3;
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
    radius = rand() % 20 + 10;
    speed = rand() % 3 + 3;
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
    radius = rand() % 20 + 10;
    speed = rand() % 3 + 3;
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
        
//------------------------------

bool checkCollisionBash(const Lander& spaceship1, const Lander& spaceship2,
const std::vector<Bashteroid>& bashteroids)
{
    // Array of two landers
    if (g.twoPlayer) {
        const Lander* spaceships[2] = {&spaceship1, &spaceship2};

        for (int i = 0; i < 2; i++) {
            for (const Bashteroid& bashteroid : bashteroids) {
                float distance = sqrt(pow(spaceships[i]->pos[0] - bashteroid.x, 2) + 
                                    pow(spaceships[i]->pos[1] - bashteroid.y, 2));

                if (distance < (spaceships[i]->radius + bashteroid.radius)) {
                    return true;  // A collision is found with the Bashteroid.
                }
            }
        }
        return false; // No collisions found
    } else {
        for (const Bashteroid& bashteroid : bashteroids) { 
            float distance = sqrt(pow(spaceship1.pos[0] - bashteroid.x, 2) 
                                    + pow(spaceship1.pos[1] - bashteroid.y, 2));
            if (distance < (spaceship1.radius + bashteroid.radius)) {
                return true;
            }
        }
    }
    return false;
}

void renderBashteroid() 
{
    for (const Bashteroid& bashteroid : bashteroids) {
        glPushMatrix();
        glTranslatef(bashteroid.x, bashteroid.y, 0.0f);

        // Lines with gradient from purple to blue
        glBegin(GL_LINES);
        for (int i = 0; i < 35; i++) {
            // Purple color
            glColor3ub(128, 0, 128);  // RGB for purple
            glVertex2f((rnd() * bashteroid.radius * 2) - bashteroid.radius, 0.0);
            // Blue color
            glColor3ub(0, 0, 255);    // RGB for blue
            glVertex2f(0.0 + rnd() * 14.0 - 7.0, (50.0 + rnd() * 50.0));
        }
        glEnd();

        // Triangle fan with gradient from purple to blue
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < 360; i += 15) {
            float angle = i * 3.14159265f / 180.0f;
            float x = bashteroid.radius * cos(angle);
            float y = bashteroid.radius * sin(angle);
    
            float t = static_cast<float>(i) / 360.0f;
       
            float red = (1.0f - t) * 128.0f;  // Red channel starts at 128 for purple and goes to 0 for blue
            float green = 0.0f;                // Green channel stays at 0 for both purple and blue
            float blue = t * 255.0f + (1.0f - t) * 128.0f; // Blue channel starts at 128 for purple and goes to 255 for blue

            glColor3f(red / 255.0f, green, blue / 255.0f); // Normalize the RGB values by dividing by 255
            glVertex2f(x, y);
        }
        glEnd();
    
        glPopMatrix();
        }
}


void init_asteroids() 
{
    // the repeated code is to make each initialization of the asteroids more random.
    srand(time(NULL));
	    for (int i = 0; i < 2; ++i) {
		    float startX = rand() % g.xres;
		    float startY = g.yres;//rand() % g.yres;
		    float startRadius = rand() % 20 + 10;
		    float startSpeed = rand() % 4 + 1;
		    asteroids.push_back(Asteroid(startX, startY, startRadius, startSpeed));
        }
        for (int i = 0; i < 2; ++i) {
            float startX = rand() % g.yres;
            float startY = g.yres;
            float startRadius = rand() % 20 + 10;
            float startSpeed = rand() % 4 + 1;
            bashteroids.push_back(Bashteroid(startX, startY, startRadius, startSpeed));
        }
        for (int i = 0; i < 2; ++i) {
            float startX = rand() % g.yres;
            float startY = g.yres;
            float startRadius = rand() % 20 + 10;
            float startSpeed = rand() % 4 + 1;
            X11steroids.push_back(X11steroid(startX, startY, startRadius, startSpeed));
        }
}

void reset_asteroids() 
{
    for (int i = 0; i < 2; ++i) {
        asteroids[i].y = g.yres;
        bashteroids[i].y = g.yres;
        X11steroids[i].y = g.yres;
    }
}

void renderAsteroids() 
{
    glColor3f(1.0f, 1.0f, 1.0f);
    for (const Asteroid& asteroid : asteroids) {

        glPushMatrix();
        glTranslatef(asteroid.x, asteroid.y, 0.0f);
        glBegin(GL_LINES);
            for (int i = 0; i < 35; i++) {

                glColor3ub(255,0,0);
                glVertex2f((rnd() * asteroid.radius * 2) - asteroid.radius, 0.0);
                glColor3ub(250, 250, 0);
                glVertex2f(0.0 + rnd() * 14.0-7.0, (50.0 + rnd() * 50.0));
            }
            glEnd();

            glBegin(GL_TRIANGLE_FAN);
            for (int i= 0; i < 360; i +=15) {

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

void renderX11steroid() 
{
    glColor3f(1.0f, 1.0f, 1.0f);
    for (const X11steroid& X11steroid : X11steroids) {
        glPushMatrix();
        glTranslatef(X11steroid.x, X11steroid.y, 0.0f);
        glBegin(GL_LINES);
            for (int i = 0; i < 35; i++) {
                glColor3ub(0,0,0);
                glVertex2f((rnd() * X11steroid.radius * 2)
                - X11steroid.radius, 0.0);
                glColor3ub(50, 50, 50);
                glVertex2f(0.0 + rnd() * 14.0-7.0, (50.0 + rnd() * 50.0));
            }
        glEnd();
        glBegin(GL_TRIANGLE_FAN);
            for (int i= 0; i < 360; i +=15) {
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

bool checkCollision(const Lander& spaceship1, const Lander& spaceship2, 
const std::vector<Asteroid>& asteroids) 
{
    if (g.twoPlayer) {
    // Array of two landers
    const Lander* spaceships[2] = {&spaceship1, &spaceship2};

        for (int i = 0; i < 2; i++) {
            for (const Asteroid& asteroid : asteroids) {
                float distance = sqrt(pow(spaceships[i]->pos[0] - asteroid.x, 2) 
                    + pow(spaceships[i]->pos[1] - asteroid.y, 2));
                if (distance < (spaceships[i]->radius + asteroid.radius)) {
                    return true; 
                }
            }
        }
        return false;
    } else {
        for (const Asteroid& asteroid : asteroids) {
            float distance = sqrt(pow(spaceship1.pos[0] - asteroid.x, 2)
                + pow(spaceship1.pos[1] - asteroid.y, 2));
            if (distance < (spaceship1.radius + asteroid.radius)) {
                return true;
            }
        }
    }
    return false;
}

bool checkCollisionX11steroid(const Lander& spaceship1, 
const Lander& spaceship2, const std::vector<X11steroid>& X11steroids) 
{
    if (g.twoPlayer) {
    // Array of two landers
    const Lander* spaceships[2] = {&spaceship1, &spaceship2};

        for (int i = 0; i < 2; i++) {
            for (const X11steroid& X11steroid : X11steroids) {
                float distance = sqrt(pow(spaceships[i]->pos[0] - X11steroid.x, 2) + 
                    pow(spaceships[i]->pos[1] - X11steroid.y, 2));

                if (distance < (spaceships[i]->radius + X11steroid.radius)) {
                    return true; 
                }
            }
        }
        return false;
    } else {
        for (const X11steroid& X11steroid : X11steroids) {
            float distance = sqrt(pow(spaceship1.pos[0] - X11steroid.x, 2) 
            + pow(spaceship1.pos[1] - X11steroid.y, 2));
            if (distance < (spaceship1.radius + X11steroid.radius)) {
                return true;
            }
        }
    }
    return false;
}

const int COOLDOWN_FRAMES = 60;
int collisionCooldown = 0;
void X11steroidPhysics() 
{
    if (collisionCooldown > 0) {
		collisionCooldown--;
	} else if (checkCollisionX11steroid(lander, lander2, X11steroids)) {
		g.xres -= 25;
		g.yres -= 25;
		x11.reshape_window(g.xres, g.yres);
		collisionCooldown = COOLDOWN_FRAMES;
            if(g.xres < 110) {
                g.xres = 100;
                g.yres = 300;
            }
	}

	if (g.starsmoveback) {
		for (X11steroid& X11steroid : X11steroids) {
			X11steroid.moveback();
		}
	} else {
		for (X11steroid& X11steroid : X11steroids) {
			X11steroid.move();
		}
	}
}

void asteroidPhysics() 
{
    if (checkCollision(lander, lander2, asteroids)) {
        //cout << "Spaceship collided with an asteroid!" << endl;
        g.failed_landing = 1;
    }
    if (g.starsmoveback) {
        for (Asteroid& asteroid : asteroids) {
            asteroid.moveback();
        }
    } else {
        for (Asteroid& asteroid : asteroids) {
            asteroid.move();
        }
    }
}

void moveBashteroid() 
{
    bool currentCollisionState = checkCollisionBash(lander, lander2, bashteroids);

    if (currentCollisionState && !g.previousCollisionState) {
        g.starsmoveback = !g.starsmoveback;
    }
    
    g.previousCollisionState = currentCollisionState;
    
    if (g.starsmoveback) {
        for (Bashteroid& bashteroid : bashteroids) {
            bashteroid.moveback();
        }
    } else {
        for (Bashteroid& bashteroid : bashteroids) {
            bashteroid.move();
        }
    }
}

