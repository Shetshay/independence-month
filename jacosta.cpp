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
        ggprint8b(&r, 16, 0x00ffffff, "Main Menu");
        r.bot -= 40;
        if (menuChoice == 0)
            ggprint8b(&r, 16, 0x00ff0000, "> Start Game");
        else
            ggprint8b(&r, 16, 0x00ffffff, "Start Game");

        r.bot -= 20;
        if (menuChoice == 1)
            ggprint8b(&r, 16, 0x00ff0000, "> Options");
        else
            ggprint8b(&r, 16, 0x00ffffff, "Options");

        r.bot -= 20;
        if (menuChoice == 2)
            ggprint8b(&r, 16, 0x00ff0000, "> Quit");
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

