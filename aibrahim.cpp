//Author: Andrew Attia
//
//Date: 29 September 2023
//
//cpp file for independence day

#include <GL/glx.h>
#include <cstdlib>
#include "classesLander.h"

void spawn_newLander(){
    if (lander.pos[1] < 0.0) {
        g.failed_landing = 1;
    }
    if (lz1.pos[1] <= 0.0f) { // if lander y is less 
                             // a certain amount we make a new spawn of lander

        g.nxtlanderX1 = ((rand() % (g.ub - g.lb + 1)) + g.lb); // RANDOM X COORD GENERATOR
        g.newXcoord1 = g.nxtlanderX1;

        //g.nxtlanderY = lz.pos[1]; // this isnt working, not sure why
        lz1.pos[1] = 600.0f;
    }
    if (lz2.pos[1] <= 0.0f) { // if lander y is less 
                              // a certain amount we make a new spawn of lander

        g.nxtlanderX2 = ((rand() % (g.ub - g.lb + 1)) + g.lb); //RANDOM X COORD GENERATOR
        g.newXcoord2 = g.nxtlanderX2;

        //g.nxtlanderY = lz2.pos[1]; //this isnt working, not sure why
        lz2.pos[1] = 600.0f;

    }
    if (lz3.pos[1] <= 0.0f) { // if lander y is less 
                              // a certain amount we make a new spawn of lander

        g.nxtlanderX3 = ((rand() % (g.ub - g.lb + 1)) + g.lb); //RANDOM X COORD GENERATOR
        g.newXcoord3 = g.nxtlanderX3;

        //g.nxtlanderY = lz2.pos[1]; //this isnt working, not sure why
        lz3.pos[1] = 600.0f;

    }
    if (lz4.pos[1] <= 0.0f) { // if lander y is less 
                              // a certain amount we make a new spawn of lander

        g.nxtlanderX4 = ((rand() % (g.ub - g.lb + 1)) + g.lb); //RANDOM X COORD GENERATOR
        g.newXcoord4 = g.nxtlanderX4;

        //g.nxtlanderY = lz2.pos[1]; //this isnt working, not sure why
        lz4.pos[1] = 600.0f;

    }
    if (lz5.pos[1] <= 0.0f) { // if lander y is less 
                              // a certain amount we make a new spawn of lander

        g.nxtlanderX5 = ((rand() % (g.ub - g.lb + 1)) + g.lb); //RANDOM X COORD GENERATOR
        g.newXcoord5 = g.nxtlanderX5;

        //g.nxtlanderY = lz2.pos[1]; //this isnt working, not sure why
        lz5.pos[1] = 600.0f;

    }
}

void handle_landerInter(){
    if (lander.pos[1] <= lz1.pos[1]+10.0f && lander.pos[0] <= lz1.pos[0]+50.0f 
            && lander.pos[0] >= lz1.pos[0]-50.0f && lander.pos[1] >= lz1.pos[1]-10.0f) { 
        g.shiptrackX[0] = lander.pos[0]; 
        //cout << lander.angle << endl;
        if (lander.angle >= -8 && lander.angle <= 8){
            g.temp_velocity = lander.vel[1];
            if(g.temp_velocity <= 0.9 && g.temp_velocity >= -0.9) { // speed of rocket
                g.landed = 1; // we land on platform
                g.detach = false; //snap to platform 
                if(g.detach == false && g.keys[XK_space]) //If snapped and space bar, detach
                {
                    g.detach = true;
                }
            }
            g.landed = 0;
        }
        else {
            g.failed_landing = 1;
        }
        if (g.detach == false) { //change variable name to snapon
            lander.pos[0] = g.shiptrackX[0]; // X Axis of Ship and Lander
            lander.vel[0] = 0; //Stop the velocity so it doesnt slide off
            lander.pos[1] = lz1.pos[1]+10.0f; //Y Axis of Ship and Lander
        }
        //cout << "THIS IS THE VELOCITY: " << g.temp_velocity << endl; 
    }

    if (lander.pos[1] <= lz2.pos[1]+10.0f && lander.pos[0] <= lz2.pos[0]+50.0f 
            && lander.pos[0] >= lz2.pos[0]-50.0f && lander.pos[1] >= lz2.pos[1]-10.0f) { 
        g.shiptrackX[0] = lander.pos[0]; 
        //cout << lander.angle << endl;
        if (lander.angle >= -8 && lander.angle <= 8){
            g.temp_velocity = lander.vel[1];
            if(g.temp_velocity <= 0.9 && g.temp_velocity >= -0.9) { // speed of rocket
                g.landed = 1; // we land on platform
                g.detach = false; //snap to platform 
                if(g.detach == false && g.keys[XK_space]) //If snapped and space bar, detach
                {
                    g.detach = true;
                }
            }
            g.landed = 0;
        }
        else {
            g.failed_landing = 1;
        }
        if (g.detach == false) { //change variable name to snapon
            lander.pos[0] = g.shiptrackX[0]; // X Axis of Ship and Lander
            lander.vel[0] = 0; //Stop the velocity so it doesnt slide off
            lander.pos[1] = lz2.pos[1]+10.0f; //Y Axis of Ship and Lander
        }
        //cout << "THIS IS THE VELOCITY: " << g.temp_velocity << endl; 
    }
    if (lander.pos[1] <= lz3.pos[1]+10.0f && lander.pos[0] <= lz3.pos[0]+50.0f 
            && lander.pos[0] >= lz3.pos[0]-50.0f && lander.pos[1] >= lz3.pos[1]-10.0f) { 
        g.shiptrackX[0] = lander.pos[0]; 
        //cout << lander.angle << endl;
        if (lander.angle >= -8 && lander.angle <= 8){
            g.temp_velocity = lander.vel[1];
            if(g.temp_velocity <= 0.9 && g.temp_velocity >= -0.9) { // speed of rocket
                g.landed = 1; // we land on platform
                g.detach = false; //snap to platform 
                if(g.detach == false && g.keys[XK_space]) //If snapped and space bar, detach
                {
                    g.detach = true;
                }
            }
            g.landed = 0;
        }
        else {
            g.failed_landing = 1;
        }
        if (g.detach == false) { //change variable name to snapon
            lander.pos[0] = g.shiptrackX[0]; // X Axis of Ship and Lander
            lander.vel[0] = 0; //Stop the velocity so it doesnt slide off
            lander.pos[1] = lz3.pos[1]+10.0f; //Y Axis of Ship and Lander
        }
        //cout << "THIS IS THE VELOCITY: " << g.temp_velocity << endl; 
    }
    if (lander.pos[1] <= lz4.pos[1]+10.0f && lander.pos[0] <= lz4.pos[0]+50.0f 
            && lander.pos[0] >= lz4.pos[0]-50.0f && lander.pos[1] >= lz4.pos[1]-10.0f) { 
        g.shiptrackX[0] = lander.pos[0]; 
        //cout << lander.angle << endl;
        if (lander.angle >= -8 && lander.angle <= 8){
            g.temp_velocity = lander.vel[1];
            if(g.temp_velocity <= 0.9 && g.temp_velocity >= -0.9) { // speed of rocket
                g.landed = 1; // we land on platform
                g.detach = false; //snap to platform 
                if(g.detach == false && g.keys[XK_space]) //If snapped and space bar, detach
                {
                    g.detach = true;
                }
            }
            g.landed = 0;
        }
        else {
            g.failed_landing = 1;
        }
        if (g.detach == false) { //change variable name to snapon
            lander.pos[0] = g.shiptrackX[0]; // X Axis of Ship and Lander
            lander.vel[0] = 0; //Stop the velocity so it doesnt slide off
            lander.pos[1] = lz4.pos[1]+10.0f; //Y Axis of Ship and Lander
        }
        //cout << "THIS IS THE VELOCITY: " << g.temp_velocity << endl; 
    }
    if (lander.pos[1] <= lz5.pos[1]+10.0f && lander.pos[0] <= lz5.pos[0]+50.0f 
            && lander.pos[0] >= lz5.pos[0]-50.0f && lander.pos[1] >= lz5.pos[1]-10.0f) { 
        g.shiptrackX[0] = lander.pos[0]; 
        //cout << lander.angle << endl;
        if (lander.angle >= -8 && lander.angle <= 8){
            g.temp_velocity = lander.vel[1];
            if(g.temp_velocity <= 0.9 && g.temp_velocity >= -0.9) { // speed of rocket
                g.landed = 1; // we land on platform
                g.detach = false; //snap to platform 
                if(g.detach == false && g.keys[XK_space]) //If snapped and space bar, detach
                {
                    g.detach = true;
                }
            }
            g.landed = 0;
        }
        else {
            g.failed_landing = 1;
        }
        if (g.detach == false) { //change variable name to snapon
            lander.pos[0] = g.shiptrackX[0]; // X Axis of Ship and Lander
            lander.vel[0] = 0; //Stop the velocity so it doesnt slide off
            lander.pos[1] = lz5.pos[1]+10.0f; //Y Axis of Ship and Lander
        }
        //cout << "THIS IS THE VELOCITY: " << g.temp_velocity << endl; 
    }
}
