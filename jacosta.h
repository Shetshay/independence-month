//Jacobs header file for jacosta.cpp
#ifndef _JACOSTA_H
#define _JACOSTA_H

extern void spawn_newLander();
extern void handle_landerInter();



class Global {
    public:
        int lives = 3;
        int xres, yres;
        unsigned int keys[65536];
        int failed_landing;
        int landed;
        bool detach;
        int color_reset;
        int shiptrackX[2];
        double accptl_angle;
        double temp_velocity;
        int nxtlanderX = 200.0f;
        int nxtlanderX2 = 117.0f;
 
        int nxtlanderY = 600.0f;
        int nxtlander2Y = 600.0f;

        int newXcoord;
        int newXcoord2;


        int lb = 50.0f;
        int ub = 350.0f;
        Global() {
            xres = 400;
            yres = 600;
            failed_landing = 0;
            landed = 0;
            color_reset = 0;
            accptl_angle = 90;
            temp_velocity = 0.0;
        }
};

 extern Global g;

class Lz {
    //landing zone
    public:
        float pos[2];
        float width;
        float height;
        Lz() { // Landing zone
            pos[0] = 200.0f; //X axis of platform
            pos[1] = 350.0f; //Y axis of platform
            width =  50.0f;
            height =  10.0f;
        }
}; 

extern Lz lz;

class Lz2 {
    //landing zone
    public:
        float pos[2];
        float width;
        float height;
        Lz2() { // Landing zone
            pos[0] = 117.0f; //X axis of platform
            pos[1] = 1000.0f; //Y axis of platform
            width =  50.0f;
            height =  10.0f;
        }
}; 

extern Lz2 lz2;


class Lander {
    //the rocket
    public:
        float pos[2];
        float vel[2];
        float verts[3][2];
        float thrust;
        double angle;
        Lander() {
            init();
        }
        void init() {
            pos[0] = 200.0f;
            pos[1] = g.yres - 60.0f;

//#define TESTING
//#ifdef TESTING
            //pos[0] = 200.0f; //X axis of ship
            //pos[1] = 400.0f; //Y axis of ship
//#endif

            vel[0] = vel[1] = 0.0f;
            //3 vertices of triangle-shaped rocket lander
            verts[0][0] = -10.0f;
            verts[0][1] =   0.0f;
            verts[1][0] =   0.0f;
            verts[1][1] =  30.0f;
            verts[2][0] =  10.0f;
            verts[2][1] =   0.0f;
            angle = 0.0;
            thrust = 0.0f;
            g.failed_landing = 0;
        }
}; 

extern Lander lander;


#endif