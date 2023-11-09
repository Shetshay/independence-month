//header for Andrew Ibrahim

#ifndef _AIBRAHIM_H
#define _AIBRAHIM_H

extern void spawn_newLander();
extern void handle_landerInter();

#include <string>

void readHighScores();
void displayHighScores();
void sendHighScore(const std::string& playerName, int highScore);


#endif
