# Cyber-Pong
My first pong game! Should be a fun learning experience using SFML
To compile with gnu makefile:
pong: pong.cpp
	g++ -c pong.cpp
	g++ pong.o -o pong -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
