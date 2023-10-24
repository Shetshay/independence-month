//
// Author:    John Pocasangre
// Created:   09.29.2023
// 
// (c) Copyright by Jpocasangre.
//

#ifndef JPOCASANGRE_H
#define JPOCASANGRE_H
#include <vector>

// class FailureIndicator {
// public:
//     void drawCircle(float x, float y, float radius);
//     float explosionRadius = 0.0f;
//     bool isExploding = false;
// };

class FailureIndicator {
public:
    void drawExplosion(float x, float y);
    std::vector<float> explosionRadii;
    bool isExploding = false;
};

class Record {
public:
    int distance(int x, int y);
};

//int total_running_time(const bool get)
#endif