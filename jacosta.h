//Jacobs header file for jacosta.cpp

#ifndef _JACOSTA_H
#define _JACOSTA_H

extern void handleMenu(void);
extern void endMenu(void);
extern int countPhysics(bool);
extern int total_running_time(bool);
extern void move_stars(void);
extern void init_stars(void);
extern void render_stars(void);
extern void render_slowstars(void);
extern void render_stagstars(void);
extern bool timer(int);
extern int countHighscore(bool);

#endif
