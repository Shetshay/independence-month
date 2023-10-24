#include <GL/glx.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <iostream>
#include "jpocasangre.h"
#include <vector>
using namespace std;

// void FailureIndicator::drawCircle(float x, float y, float radius) {
//     glColor3ub(250, 0, 0); // Set color to red
//     glPushMatrix();
//     glTranslatef(x, y, 0.0f);
//     glBegin(GL_POLYGON);
//     const int num_segments = 100;
//     for(int i = 0; i < num_segments; i++) {
//         float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
//         float dx = radius * cosf(theta);
//         float dy = radius * sinf(theta);
//         glVertex2f(dx, dy);  
//     }
//     glEnd();
//     glPopMatrix();
// }

void FailureIndicator::drawExplosion(float x, float y)
{
    const int num_segments = 100;

    for (float radius : explosionRadii) {
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i <= num_segments; i++) {
            float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
            float dx = radius * cosf(theta);
            float dy = radius * sinf(theta);
            glVertex2f(x + dx, y + dy);
        }
        glEnd();
    }
}

int Record :: distance(int x, int y){


return 0;
}