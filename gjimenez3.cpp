//Gustavo Jimenez
//working on adding bullets to lander frame

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

void lander_boundaries() 
{
    if (lander.pos[0] < 0)
        lander.pos[0] = g.xres;

    if (lander.pos[0] > g.xres) 
        lander.pos[0] = 0;

    if (lander.pos[1] > g.yres - 30) 
        lander.pos[1] = g.yres - 30;
    
    if (lander.pos[1] < 0)
        g.failed_landing = 1;
}

void render_iceblock () 
{
    	//Draw LZ
	glPushMatrix();
	if(lander.pos[0] <= lz.pos[0] + 20 && lander.pos[0] >= lz.pos[0] - 20 && lander.pos[1] <= lz.pos[1] + 20 && lander.pos[1] >= lz.pos[1] - 20) {
        g.color = 1.0f;
    }
    glColor3ub(173, 216, 230);
    glTranslatef(lz.pos[0], lz.pos[1], 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-lz.width, -lz.height);
    glVertex2f(-lz.width,  lz.height);
    glVertex2f( lz.width,  lz.height);
    glVertex2f( lz.width, -lz.height);
    glEnd();
	glPopMatrix();
}
