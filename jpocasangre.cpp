//
// Author:    John Pocasangre
// Created:   09.29.2023
// 
// (c) Copyright by Jpocasangre.
//

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
FailureIndicator2::FailureIndicator2() {
}

void FailureIndicator2::updateFragments() {
    for (auto& fragment : fragments) {
        if (fragment.active) {
            fragment.vertices[0][0] += fragment.velocity[0];
            fragment.vertices[0][1] += fragment.velocity[1];
            fragment.vertices[1][0] += fragment.velocity[0];
            fragment.vertices[1][1] += fragment.velocity[1];
            fragment.vertices[2][0] += fragment.velocity[0];
            fragment.vertices[2][1] += fragment.velocity[1];
            fragment.angle += fragment.angularVelocity;
            if (fragment.vertices[0][0] < 0 || fragment.vertices[0][1] < 0) {
                fragment.active = false;
            }
        }
    }
}

void FailureIndicator2::createFragments(float x, float y, int numFragments) {
    fragments.clear(); 
    srand(static_cast<unsigned int>(time(NULL))); 

    for (int i = 0; i < numFragments; ++i) {

        float angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f * M_PI;
        // speed 
        float speed = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * maxSpeed; 

        TriangleFragment frag;
        frag.vertices[0][0] = x; 
        frag.vertices[0][1] = y;
        // randomness
        frag.vertices[1][0] = x + cos(angle + M_PI / 6) * fragmentSize; 
        frag.vertices[1][1] = y + sin(angle + M_PI / 6) * fragmentSize;
        frag.vertices[2][0] = x + cos(angle - M_PI / 6) * fragmentSize;
        frag.vertices[2][1] = y + sin(angle - M_PI / 6) * fragmentSize;
        // how far it goes away from the center of the ship
        frag.velocity[0] = cos(angle) * speed;
        frag.velocity[1] = sin(angle) * speed;
        // how fast it spins 
        frag.angularVelocity = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 0.5f) * maxAngularSpeed; 
        frag.active = true;
        fragments.push_back(frag);
    }
}

void FailureIndicator2::drawFragments() {
    glBegin(GL_TRIANGLES);
    for (auto& fragment : fragments) {
        if (fragment.active) {
            glPushMatrix();
            glTranslatef(fragment.vertices[0][0], fragment.vertices[0][1], 0);
            glRotatef(fragment.angle, 0, 0, 1);
            glTranslatef(-fragment.vertices[0][0], -fragment.vertices[0][1], 0);

            //color of the shrimp(the ship)
           srand(static_cast<unsigned int>(time(nullptr)));
            int X = (rand() % 4) + 1;
            if (X == 1) {
                glColor4f(1.0f, 1.0f, 0.0f, 1.0f); 
            } else if (X == 2) {
                glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            } else if (X == 3) {
                glColor4f(0.0f, 1.0f, 1.0f, 1.0f); 
            } else if (X == 4) {
                glColor4f(0.9f, 0.7f, 1.0f, 1.0f); 
            } else if (X == 5) {
                glColor4f(1.0f, 0.5f, 0.0f, 1.0f);
            } else if (X == 6) {
                glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
            }
            //cout << "Random Color Value: " << X << endl;

            // color of the remains of the shrimp
            // glColor4f(3.0f, 1.0f, 3.0f, 1.5f); 
            // the remains of the ship being drawn
            glVertex2f(fragment.vertices[0][0], fragment.vertices[0][1]);
            glVertex2f(fragment.vertices[1][0], fragment.vertices[1][1]);
            glVertex2f(fragment.vertices[2][0], fragment.vertices[2][1]);
            glPopMatrix();
        }
    }
    glEnd();
}
void Record::setStart(double x, double y) {
    startX = x;
    startY = y;
}

void Record::setEnd(double x, double y) {
    endX = x;
    endY = y;
}

double Record::getDistance() {
    double dx = endX - startX;
    double dy = endY - startY;
    total = total + sqrt(dx * dx + dy * dy);
    return total;
}