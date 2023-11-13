//Jacobs header file for jacosta.cpp

#ifndef _JACOSTA_H
#define _JACOSTA_H

extern void handleMenu(void);
extern void endMenu(void);
extern int countPhysics(bool);
extern int total_running_time(bool);
extern void move_stars();
extern void init_stars();
extern void render_stars();
extern void render_slowstars();
extern void render_stagstars();
extern bool timer();

#endif