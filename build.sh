#!/usr/bin/bash
g++ -o audioplayer audioplayer.cpp -I./include/ -L./lib/ -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lsfml-audio-d -lsfml-system-d
