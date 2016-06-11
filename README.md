# Cyber-Pong
My first pong game using SFML. This program is still being worked on and not officially released.

INSTALL

Make sure you have SFML version 2.3 or later
if using Arch linux grab package from official repo
pacman -S sfml

To compile with gnu makefile on linux:

   	   pong: pong.cpp

			g++ pong.o -o pong -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
tested on linux. May take some configuring to make it work on windows until official support .

HOW TO CONTRIBUTE

Do not add anything that has not been tested to the Master branch. All changes must be added to the test or other branches. Once it is reviewed and approved then it can be added to the master branch