SRCFILES = aibrahim.cpp gjimenez3.cpp jacosta.cpp jalejo.cpp jpocasangre.cpp

all: lander 
  
lander: lander.cpp aibrahim.cpp gjimenez3.cpp jacosta.cpp jalejo.cpp jpocasangre.cpp log.cpp
	g++ lander.cpp $(SRCFILES) log.cpp libggfonts.a -Wall -olander -lX11 -lGL -lGLU -lm -lcurl -lopenal -lalut -Wextra \
	-D USE_OPENAL_SOUND \
	/usr/lib/x86_64-linux-gnu/libopenal.so \
	/usr/lib/x86_64-linux-gnu/libalut.so
clean:
	rm -f lander
