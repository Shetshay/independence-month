//
// Author:    John Pocasangre
// Created:   09.29.2023
// 
// (c) Copyright by Jpocasangre.
//

#ifndef JPOCASANGRE_H
#define JPOCASANGRE_H
#include <vector>
#include <cmath>

class FailureIndicator {
public:
    void drawExplosion(float x, float y);
    std::vector<float> explosionRadii;
    bool isExploding = false;
};

class FailureIndicator2 {
public:
    struct TriangleFragment {
        float vertices[3][2]; 
        float velocity[2];    
        float angle;          
        float angularVelocity; 
        bool active;          
        TriangleFragment() : angle(0.0f), angularVelocity(0.0f), active(false) {
        }
    };
    const float maxSpeed = 45.0f; 
    const float maxAngularSpeed = 360.0f; 
    const float fragmentSize = 10.0f; 
    std::vector<TriangleFragment> fragments; 
    float explosionCenterX, explosionCenterY; 
    FailureIndicator2();
    void createFragments(float x, float y, int numFragments);
    void updateFragments(); 
    void drawFragments();  
    void reset();  
};

class Record {
public:
    double startX = 0, startY = 0;
    double endX = 0, endY = 0;
    double cumulativeDistance = 0;
    double total = 0;

    void setStart(double x, double y);
    void setEnd(double x, double y);
    double getDistance();
};

#endif 
