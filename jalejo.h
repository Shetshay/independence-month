//Author: Justin Alejo
//Created on 9/29/2023
#ifndef _JALEJO_H
#define _JALEJO_H

#include <iostream>
using namespace std;

extern void render_stars();

struct Star{

	float x, y;
	Star() {
	x = 0.0f;
	y = 0.0f;
	}
	Star(float ex, float why){
	x = ex;
	y = why;
	}

};



#endif
