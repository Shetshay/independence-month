
all: lander 
  
lander: lander.cpp
	g++ lander.cpp -Wall -olander -lX11 -lGL -lGLU -lm
  
clean:
	rm -f lander
