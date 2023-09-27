//justin alejo
#include <GL/glx.h>
//#include "land.h"
//#include "lander.cpp"

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
