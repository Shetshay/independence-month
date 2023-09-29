//justin alejo
#include <GL/glx.h>
//#include "land.h"
//#include "lander.cpp"
#include "jalejo.h"
using namespace std;

void test_function(){

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3ub(250, 200, 90); glVertex2i(0,0);
    glColor3ub(100,  80, 200); glVertex2i(0, 500);
    glColor3ub(100, 80, 200); glVertex2i(0, 500);
    glColor3ub(250, 200, 90); glVertex2i(0,0);
    glPopMatrix();
    glEnd();

}

Lz lz;
