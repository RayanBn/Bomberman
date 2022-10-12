#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 600

int eventLoop(void)
{
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return 0;
        }
    }
    return 1;
}

int main (void)
{
    SDL_Window *window = NULL;

    window = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    while (eventLoop()) {
        printf("nice ca continue\n");
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
