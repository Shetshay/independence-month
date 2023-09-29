
all: lander 
  
lander: lander.cpp aibrahim.cpp gjimenez3.cpp jacosta.cpp jalejo.cpp jpocasangre.cpp
	g++ lander.cpp aibrahim.cpp gjimenez3.cpp jacosta.cpp jalejo.cpp jpocasangre.cpp -Wall -olander -lX11 -lGL -lGLU -lm
  
clean:
	rm -f lander
