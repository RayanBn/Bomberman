#include "bomberman.h"

int eventLoop(void)
{
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return LEAVE;
        }
    }
    return GAME;
}

int main (void)
{
    SDL_Window *window = NULL;
    int status = GAME;
    SDL_Renderer *renderer;
    SDL_Surface *image;
    SDL_Texture *texture;
    SDL_Rect rectSize = {0, 0, 64, 64};
    SDL_Rect myRect = {0, 0, 16, 16};

    window = SDL_CreateWindow("Bomberman", 0, 0, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    image = SDL_LoadBMP("./assets/bomber.bmp");
    texture = SDL_CreateTextureFromSurface(renderer, image);
    while (status != LEAVE) {
        status = eventLoop();
        SDL_RenderCopy(renderer, texture, &myRect, &rectSize);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
