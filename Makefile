
all: lander 
  
lander: lander.cpp jacosta.cpp
	g++ lander.cpp jacosta.cpp -Wall -olander -lX11 -lGL -lGLU -lm
  
clean:
	rm -f lander
