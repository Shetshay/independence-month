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

void FailureIndicator2::reset() {
    fragments.clear();
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

//--------Laser executables---------------
Laser::Laser() 
{
    pos[0] = 0.0f;
    pos[1] = 0.0f;
    length = 20.0f;
    speed = 3.0f;
    active = false;
}

void Laser::fire(float startX, float startY) 
{
    pos[0] = startX;
    pos[1] = startY;
    active = true;
}

void Laser::move() 
{
    if (active) {
        pos[1] += speed; // Move the laser upward
    }
}

void Laser::render() 
{
    if (active) {

        float laserWidth = 5.0f; // Width of the laser rectangle

        glColor3f(0.8f, 0.0f, 0.5f); // Purple color for the laser

        glBegin(GL_QUADS);
        
        glVertex2f(pos[0] - laserWidth/2, pos[1]);
        glVertex2f(pos[0] + laserWidth/2, pos[1]);
        glVertex2f(pos[0] + laserWidth/2, pos[1] - length);
        glVertex2f(pos[0] - laserWidth/2, pos[1] - length);
        
        glEnd();
    }
}
//----------------------------------------

//----------UFO executables----------------
UFO::UFO() 
{
    pos[0] = 200.0f;
    pos[1] = 50.0f;
    radiusTop = 50.0f;
    radiusBottom = 30.0f;
    heightBottom = 20.0f;
}
//----------------------------------------

//----------AlienHead executable----------
void AlienHead::drawCircle(float cx, float cy, float r, float color[3]) 
{
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);  // Center
    for (int ii = 0; ii <= 100; ii++) {
        float theta = 2.0f * 3.1415926f * float(ii) / 100.0f;
        float dx = r * cosf(theta);
        float dy = r * sinf(theta);
        glVertex2f(cx + dx, cy + dy);
    }
    glEnd();
}

void AlienHead::drawOval(float cx, float cy, float rx, float ry, float angle, float color[3]) 
{
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);  // Center
    for (int ii = 0; ii <= 100; ii++) {
        float theta = 2.0f * 3.1415926f * float(ii) / 100.0f;
        float dx = rx * cosf(theta);
        float dy = ry * sinf(theta);
        
        float rotatedX = cx + (dx * cosf(angle) - dy * sinf(angle));
        float rotatedY = cy + (dx * sinf(angle) + dy * cosf(angle));
        
        glVertex2f(rotatedX, rotatedY);
    }
    glEnd();
}

void AlienHead::alienrender(float cx, float cy) 
{
    float headColor[3] = {0.2f, 0.9f, 0.2f};  // Yellowish color for the alien head
    float eyeColor[3] = {1.0f, 0.0f, 0.0f};   // Red color for the eyes

    // Draw the head
    drawCircle(cx, cy, 15.0f, headColor);

    // Draw the left eye as a tilted oval
    drawOval(cx - 8.0f, cy + 2.0f, 3.0f, 5.0f, 0.3f, eyeColor);

    // Draw the right eye as a tilted oval
    drawOval(cx + 8.0f, cy + 2.0f, 3.0f, 5.0f, -0.3f, eyeColor);
}
//----------------------------------------

void shootlaser() 
{
    if (g.starsmoveback) {
        //Do nothing
    } else {
        if(myUFO.pos[0] < lander.pos[0] + 5 && myUFO.pos[0] > lander.pos[0] - 5) {
        ufoLaser.fire(myUFO.pos[0], myUFO.pos[1] - myUFO.radiusBottom);
        }
    }
}

void drawOval(float cx, float cy, float rx, float ry, float color[3])
{
    int num_segments = 50;
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int ii = 0; ii <= num_segments; ii++) {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);
        float dx = rx * cosf(theta);
        float dy = ry * sinf(theta);
        glVertex2f(cx + dx, cy + dy);
    }
    glEnd();
}

void renderUFO(const UFO &ufo) {
    float mainBodyColor[3] = {0.6f, 0.6f, 0.6f};
    float cockpitColor[3] = {0.6f, 0.8f, 1.0f};
    glPushMatrix();
    drawOval(ufo.pos[0], ufo.pos[1], ufo.radiusTop, ufo.radiusBottom, mainBodyColor);

    float cockpitOffsetY = ufo.radiusBottom * 0.3f;
    drawOval(ufo.pos[0], ufo.pos[1] + cockpitOffsetY, ufo.radiusTop * 0.6f, ufo.radiusBottom * 0.5f, cockpitColor);
    alien.alienrender(ufo.pos[0], ufo.pos[1] + cockpitOffsetY);
}

void move_ufo() 
{
    if(myUFO.pos[0] < 0) {
        g.inRange = false;
    }

    if(myUFO.pos[0] > g.xres) {
        g.inRange = true;
    }

    if(g.inRange) {
        myUFO.pos[0]--;
    } else {
        myUFO.pos[0]++;
    }
}