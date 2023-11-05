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
            ggprint8b(&r, 16, 0x009900FF, "> Retry");
        else
            ggprint8b(&r, 16, 0x00ffffff, "Retry");

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

