#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <unistd.h>
#include <fcntl.h>	

#define WIDTH 800
#define HEIGHT 600

enum status {
    GAME = 0,
    LEAVE,
    PAUSE,
    SETTINGS,
};

#endif
