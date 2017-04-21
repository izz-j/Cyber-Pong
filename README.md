# Cyber-Pong

![Cyber-Pong Preview](www.github.com/izz-jCyber-Pong/pong1.gif)
My first pong game using SFML. This program is still being worked on and is not
officially released.

#INSTALL

Make sure you have SFML version 2.3 or later. You can learn about downloading
SFML for Linux in [that project's
documentation](http://www.sfml-dev.org/tutorials/2.3/start-linux.php).

If you're using Arch Linux, you can grab the package from the official repo:
    
    pacman -S sfml

##Compiling Cyber-Pong
After cloning this repo, compile with g++ on Linux:

    g++ -c pong.cpp
    g++ pong.o -o pong -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

Cyber-Pong is tested on Linux. It may take some configuring to make it work on
Windows until official support is added.

#HOW TO CONTRIBUTE

Do not add anything that has not been tested to the `release` branch. All changes
must be added to `dev` or other branches. Once it is reviewed and approved,
then it can be added to the `release` branch.
