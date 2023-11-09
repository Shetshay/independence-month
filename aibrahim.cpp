//Author: Andrew Attia
//
//Date: 29 September 2023
//
//cpp file for independence day
using namespace std;
#include <GL/glx.h>
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <iostream>
#include "classesLander.h"
#include "log.h"
#include "fonts.h"
#include <vector>
#include <curl/curl.h>
#include <string>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}
void sendHighScore(const std::string& playerName, int highScore) {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if (curl) {
        // Set the URL of your PHP script
        curl_easy_setopt(curl, CURLOPT_URL, "https://cs.csub.edu/~aibrahim/independance_day/highscore.php");

        // Specify that it's a POST request
        curl_easy_setopt(curl, CURLOPT_POST, 1);

        // Provide the data to be sent in the POST request
        std::string postData = "name=" + playerName + "&score=" + std::to_string(highScore);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());

        // Set a callback function to handle response data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        // Create a string to hold the response data
        std::string response;

        // Set the response string as the user data for the callback
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // Print the response from the PHP script
            std::cout << "Response from server: " << response << std::endl;
        }

        // Clean up
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}




std::string readHighScores() {
    std::string url = "https://cs.csub.edu/~aibrahim/independance_day/highscore.txt";
    CURL* curl = curl_easy_init();

    std::string result;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }

    return result;
}

void displayHighScores() {
    std::string highScores = readHighScores();
    std::cout << "High Scores:\n" << highScores << std::endl;
}

void renderName() {
    // Adding the player name display
    glDisable(GL_BLEND); // Disable blending temporarily
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glColor3ub(255, 255, 255);
    Rect r;
    r.bot = 520;
    r.left = 10;
    r.center = 0;
    ggprint8b(&r, 16, 0x009900FF, "Player Name: %s", g.playerName.c_str());
    glPopMatrix();
    glEnable(GL_BLEND); // Enable blending again
    x11.swapBuffers();
}

void askForName(std::string& playerName) {
    if (!playerName.empty()) {
        return;
    }
    XEvent e;
    KeySym key;
    char text[255];

    playerName = ""; // Clear the playerName

    bool done = false;
    while (!done) {
        // Check for events without blocking
        while (XPending(x11.getDisplay())) {
            XNextEvent(x11.getDisplay(), &e);
            if (e.type == KeyPress) {
                int i = XLookupString(&e.xkey, text, 255, &key, 0);
                if (i == 1 && (text[0] == 13 || text[0] == 10)) {
                    // Enter key pressed, exit the loop
                    done = true;
                } else if (i == 1 && text[0] == 8) {
                    // Backspace pressed, remove a character
                    if (!playerName.empty()) {
                        playerName.pop_back();
                    }
                } else {
                    // Add the pressed character to playerName
                    playerName += text[0];
                }
            }
            renderName(); // Update the displayed name
        }
    }
}



/*
// Function to update high score
void updateHighScore(const std::string& username, int score) {
    // Construct the URL (replace with your actual server URL)
    std::string url = "https://cs.csub.edu/~aibrahim/independance_day/highscore.php?action=update&username=" + username + "&score=" + std::to_string(score);

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL* curl = curl_easy_init();

    if (curl) {
        // Set the URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Perform the request
        CURLcode res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Cleanup
        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }
}


// Function to read high score
std::string readHighScore() {
    // Construct the URL
    std::string url = "https://cs.csub.edu/~aibrahim/independance_day/highscore.php?action=read";

    // ... (similar libcurl setup)

    // Perform the request and store the response
    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // ... (perform the request and cleanup)

    return response;
}

*/





/*
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
}*/
