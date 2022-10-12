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

char *readMap(char *filepath)
{
    int mapSize = 120;
    char *string = malloc(sizeof(char) * mapSize);
    int fd = open(filepath, O_RDONLY);

    read(fd, string, mapSize);
    close(fd);
    write(1, string, 120);
    return string;
}

void createMap(SDL_Texture *texture, SDL_Renderer *renderer)
{
    int nbMapColumns = 20;
    int nbMapLines = 6;
    SDL_Texture ***textureMap = malloc(sizeof(SDL_Texture **) * (nbMapLines + 1));
    SDL_Rect rectSize = {0, 0, 64, 64};
    SDL_Rect myRect = {16 * 6, 0, 16, 16};
    int posx = 0;
    int posy = 0;

    for (int y = 0; y < nbMapLines; y++) {
        textureMap[y] = malloc(sizeof(SDL_Texture *) * (nbMapColumns + 1));
        for (int x = 0; x < nbMapColumns; x++) {
            rectSize.x = posx;
            SDL_RenderCopy(renderer, texture, &myRect, &rectSize);
            SDL_RenderPresent(renderer);
            posx += 64;
        }
        rectSize.y = posy;
        posy += 64;
        posx = 0;
    }
}

int main (void)
{
    SDL_Window *window = NULL;
    int status = GAME;
    SDL_Renderer *renderer;
    SDL_Surface *mapTileset;
    SDL_Texture *texture;
    readMap("./maps/map1.txt");

    window = SDL_CreateWindow("Bomberman", 0, 0, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    mapTileset = SDL_LoadBMP("./assets/bomber.bmp");
    texture = SDL_CreateTextureFromSurface(renderer, mapTileset);
    while (status != LEAVE) {
        status = eventLoop();
        createMap(texture, renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(mapTileset);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
