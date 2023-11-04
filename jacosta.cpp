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

/*extern Global g;
extern Lz1 lz1;
extern Lz2 lz2;
extern Lz3 lz3;
extern Lz4 lz4;
extern Lz5 lz5;
extern Lander lander;
extern X11_wrapper x11;*/


void handleMenu() {
    int menuChoice = 0;
    bool inMenu = true;

    while (inMenu) {
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
        if (menuChoice == 0)
            ggprint8b(&r, 16, 0x009900FF, "> Start Game");
        else
            ggprint8b(&r, 16, 0x00ffffff, "Start Game");

        r.bot -= 20;
        if (menuChoice == 1)
            ggprint8b(&r, 16, 0x009900FF, "> Options");
        else
            ggprint8b(&r, 16, 0x00ffffff, "Options");

        r.bot -= 20;
        if (menuChoice == 2)
            ggprint8b(&r, 16, 0x009900FF, "> Quit");
        else
            ggprint8b(&r, 16, 0x00ffffff, "Quit");

        glPopMatrix();
        x11.swapBuffers();

        // Handle menu input
        XEvent e;
        while (XCheckWindowEvent(x11.getDisplay(), x11.getWindow(), KeyPressMask, &e)) {
            if (e.type == KeyPress) {
                if (e.xkey.keycode == 39) {
                    // 'S' key to select menu option
                    if (menuChoice == 0) {
                        //cout << "pressed s" << endl;
                        inMenu = false;  // Start the game
                    } else if (menuChoice == 1) {
                        // Open Options menu (customize this part)
                        // Example: inOptions = true;
                    } else if (menuChoice == 2) {
                        // Quit the game
                        exit(0);
                    }
                } else if (e.xkey.keycode == 111) {
                    // Up arrow key
                    menuChoice = (menuChoice + 2) % 3;
                } else if (e.xkey.keycode == 116) {
                    // Down arrow key
                    menuChoice = (menuChoice + 1) % 3;
                }
            }
        }
    }
}

void endMenu() {
    int menuChoice = 0;
    bool inMenu = true;

   while (inMenu) {
        glClear(GL_COLOR_BUFFER_BIT);
        glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        Rect r;
        r.center = 0;
        r.bot = g.yres - 20;
        r.left = 10;

        // Display menu options
        ggprint8b(&r, 16, 0x009966FF, "GAME OVER");
        r.bot -= 40;
        if (menuChoice == 0)
            ggprint8b(&r, 16, 0x009900FF, "> Retry");
        else
            ggprint8b(&r, 16, 0x00ffffff, "Retry");

        r.bot -= 20;
        if (menuChoice == 1)
            ggprint8b(&r, 16, 0x009900FF, "> Scores");
        else
            ggprint8b(&r, 16, 0x00ffffff, "Scores");

        r.bot -= 20;
        if (menuChoice == 2)
            ggprint8b(&r, 16, 0x009900FF, "> Quit");
        else
            ggprint8b(&r, 16, 0x00ffffff, "Quit");
        
        glPopMatrix();
        x11.swapBuffers();
        
        XEvent e;
        while (XCheckWindowEvent(x11.getDisplay(), x11.getWindow(), KeyPressMask, &e)) {
            if (e.type == KeyPress) {
                if (e.xkey.keycode == 39) {
                    // 'S' key to select menu option
                    if (menuChoice == 0) {
                        //cout << "pressed s" << endl;
                        inMenu = false;  // Start the game
                    } else if (menuChoice == 1) {
                        // Open Scores (customize this part)
                        // Example: inScores = true;
                    } else if (menuChoice == 2) {
                        // Quit the game
                        exit(0);
                    }
                } else if (e.xkey.keycode == 111) {
                    // Up arrow key
                    menuChoice = (menuChoice + 2) % 3;
                } else if (e.xkey.keycode == 116) {
                    // Down arrow key
                    menuChoice = (menuChoice + 1) % 3;
                }
            }
        }
    }
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

