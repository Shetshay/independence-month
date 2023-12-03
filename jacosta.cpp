//Jacobs Source file for CMPS3350 
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
#include "log.h"
#include "fonts.h"
#include "classesLander.h"

const int NUM_STARS = 100;

void handleMenu() {
        glClear(GL_COLOR_BUFFER_BIT);
        glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        Rect r;
        r.center = 0;
        r.bot = g.yres - 20;
        r.left = 10;

        // Display menu options
        ggprint8b(&r, 16, 0x009966FF, "Main Menu");
        r.bot -= 40;
        if (g.menuChoice == 0)
            ggprint8b(&r, 16, 0x009900FF, "> Single Player");
        else
            ggprint8b(&r, 16, 0x00ffffff, "Single Player");

        r.bot -= 20;
        if (g.menuChoice == 1)
            ggprint8b(&r, 16, 0x009900FF, "> Two Player");
        else
            ggprint8b(&r, 16, 0x00ffffff, "Two Player");

        r.bot -= 20;
        if (g.menuChoice == 2)
            ggprint8b(&r, 16, 0x009900FF, "> Scores");
        else
            ggprint8b(&r, 16, 0x00ffffff, "Scores");

        r.bot -= 20;
        if (g.menuChoice == 3)
            ggprint8b(&r, 16, 0x009900FF, "> Quit");
        else
            ggprint8b(&r, 16, 0x00ffffff, "Quit");


        glPopMatrix();
        x11.swapBuffers();
}

void endMenu() {
        glClear(GL_COLOR_BUFFER_BIT);
        glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        Rect r;
        r.center = 0;
        r.bot = g.yres - 20;
        r.left = 10;

        ggprint8b(&r, 16, 0x009966FF, "GAME OVER");
        r.bot -= 40;
        if (g.menuChoice == 0)
            ggprint8b(&r, 16, 0x009900FF, "> Back to Menu");
        else
            ggprint8b(&r, 16, 0x00ffffff, "Back to Menu");

        r.bot -= 20;
        if (g.menuChoice == 1)
            ggprint8b(&r, 16, 0x009900FF, "> Scores");
        else
            ggprint8b(&r, 16, 0x00ffffff, "Scores");

        r.bot -= 20;
        if (g.menuChoice == 2)
            ggprint8b(&r, 16, 0x009900FF, "> Quit");
        else
            ggprint8b(&r, 16, 0x00ffffff, "Quit");
        
        glPopMatrix();
        x11.swapBuffers();
}

// function to count physics
int countPhysics(bool get){
    static int test = 0;
    if (!get) {
        test++;
    }
    return test;
}
void init_stars() 
{ 
    srand(time(NULL));
    for (int i = 0; i < NUM_STARS; i++) {
        float x = static_cast<float>(rand() % g.xres);
        float y = static_cast<float>(rand() % g.yres);
        stars[i] = Star(x, y);
        acidstars[i] = Star(x - 2, y - 2);
    }
    for (int i = 0; i < NUM_STARS; i++) {
        float x = static_cast<float>(rand() % g.xres);
        float y = static_cast<float>(rand() % g.yres);
        stagstars[i] = Star(x,y);
        acidstagstars[i] = Star(x - 2 ,y - 2);
    }
    for (int i = 0; i < NUM_STARS; i++) {
        float x = static_cast<float>(rand() % g.xres);
        float y = static_cast<float>(rand() % g.yres);
        slowstars[i] = Star(x,y);
        acidslowstars[i] = Star(x - 2, y - 2);

    }
}

void move_stars() 
{
    if (g.starsmoveback) {
        for(int j = 0; j < 100; j++) {
            stars[j].y += 1.0f;
            acidstars[j].y += 1.0f;
            slowstars[j].y += 0.5f;
            acidslowstars[j].y += 0.5f;
            stagstars[j].y += 0.25f;
            acidstagstars[j].y += 0.25f;
            if(stars[j].y > g.yres) {
                stars[j].y = 0;
                acidstars[j].y = 0 - 2;
            }
            if(slowstars[j].y > g.yres) {
                slowstars[j].y = 0;
                acidslowstars[j].y = 0 - 2;
            }
            if(stagstars[j].y > g.yres) {
                stagstars[j].y = 0;
                acidstagstars[j].y = 0 - 2;
            }
        }
    } else {
        for (int j = 0; j < 100; j++) {
            stars[j].y -= 1.0f;
            acidstars[j].y -= 1.0f;
            slowstars[j].y -= 0.5f;
            acidslowstars[j].y -= 0.5f;
            stagstars[j].y -= 0.25f;
            acidstagstars[j].y -= 0.25f;
            if (stars[j].y < 0) {
                stars[j].y = g.yres;
                acidstars[j].y = g.yres - 2;
            }
            /*if (acidstars[j].y < 0)
                acidstars[j].y = g.yres;*/                
            if (slowstars[j].y < 0) {
                slowstars[j].y = g.yres;
                acidslowstars[j].y = g.yres - 2;
            }
            if (stagstars[j].y < 0) {
                stagstars[j].y = g.yres;
                acidstagstars[j].y = g.yres - 2;
            }
	    }
    }
}

void render_stars()
{

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    for(int i = 0; i < NUM_STARS; i++){

        glVertex2f(stars[i].x, stars[i].y);
        //glVertex2f(acidstars[i].x, acidstars[i].y);
    }
    for(int i = 0; i < NUM_STARS; i++) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(acidstars[i].x, acidstars[i].y);
    }
    glEnd();
}

void render_stagstars()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    for(int i = 0; i < NUM_STARS; i++){

        glVertex2f(stagstars[i].x, stagstars[i].y);
    }
    for(int i = 0; i < NUM_STARS; i++) {
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(acidstagstars[i].x, acidstagstars[i].y);
    }
    glEnd();
}

void render_slowstars()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    for(int i = 0; i < 100; i++){

        glVertex2f(slowstars[i].x, slowstars[i].y);
    }
    for(int i = 0; i < NUM_STARS; i++) {
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(acidslowstars[i].x, acidslowstars[i].y);
    }
    glEnd();
}

bool timer(int timeTaken) {
    static int start_time = 1;
    if (start_time == 1) {
        start_time = time(NULL);
    }
    
    int elapsed = time(NULL) - start_time;
    //cout << elapsed << endl;

    if (elapsed >= timeTaken) {
        //cout << elapsed << endl;
        elapsed = 0;
        start_time = 1; // Reset the timer
        return true;  // 3 seconds have passed
    }
    return false;
}

int total_running_time(const bool get){
    static int firsttime = 1;
    static int start_time;
    if(firsttime) {
        start_time = time(NULL);
        firsttime = 0;
    }
    if(get) {
        return time(NULL) - start_time;
    }
    return 0;
}

int countHighscore(bool reset){
    static int score = 0;
    static time_t lastIncrement = 0;
    if(reset) {
        score = 0;
        lastIncrement = time(NULL);
    } else {
        if(!g.failed_landing){
        if(g.starsmoveback == false){
        time_t currentTime = time(NULL);
        if (currentTime - lastIncrement >= 2){
            score++;
            lastIncrement = currentTime;
        }
        }else{
            time_t currentTime = time(NULL);
            if (currentTime - lastIncrement >= 2){
            score--;
            lastIncrement = currentTime;
            if(score <= 0){
                score = 0;
            }
        }
        }
    }
    }

    return score;
}

    





