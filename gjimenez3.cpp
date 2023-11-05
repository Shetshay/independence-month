//Gustavo Jimenez
//working on adding bullets to lander frame

//#include <GL/glx.h>
//#include <fonts.h>
#include <GL/glx.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <iostream>
#include "gjimenez3.h"
#include "classesLander.h"
#include <vector>
using namespace std;

void render_space_color()
{
    glPushMatrix();
    	glBegin(GL_QUADS);
    		//Each vertex has a color.
    		glColor3ub(g.purp, 0, g.purp); glVertex2i(0, 0);
    		glColor3ub(g.inversepurp,  0, g.inversepurp); glVertex2i(0, g.yres);
    		glColor3ub(g.purp,  0, g.purp); glVertex2i(g.xres, g.yres);
    		glColor3ub(g.inversepurp, 0,  g.inversepurp); glVertex2i(g.xres, 0);

            if(g.purp == 0) {
                g.isDecreasing = false;
            }
            if (g.purp == 100) {
                g.isDecreasing = true;
            }
            if(g.isDecreasing) {
                g.purp--;
            } else {
                g.purp++;
            }
            g.inversepurp = 100 - g.purp;

    	glEnd();
    	glPopMatrix();
}
