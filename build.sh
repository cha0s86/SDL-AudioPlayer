#!/usr/bin/bash
echo Building for linux
g++ -o build/linux/audioplayer audioplayer.cpp -I./include/ -L./lib/ -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf
