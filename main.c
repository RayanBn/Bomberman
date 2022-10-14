#include "bomberman.h"

int eventLoop(SDL_Rect *playerPos)
{
    SDL_Event event;
    int speed = 5;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return LEAVE;
        if (event.key.keysym.sym == SDLK_LEFT)
            playerPos->x -= speed;
        if (event.key.keysym.sym == SDLK_RIGHT)
            playerPos->x += speed;
        if (event.key.keysym.sym == SDLK_UP)
            playerPos->y -= speed;
        if (event.key.keysym.sym == SDLK_DOWN)
            playerPos->y += speed;
    }
    return GAME;
}

char *readMap(char *filepath)
{
    int mapSize = 255;
    char *string = malloc(sizeof(char) * mapSize);
    int fd = open(filepath, O_RDONLY);

    read(fd, string, mapSize);
    close(fd);
    return string;
}

SDL_Rect checkTexture(char c)
{
    SDL_Rect rect;

    if (c == 'x')
        rect = (SDL_Rect){16 * 0, 16 * 0, 16, 16};
    if (c == '.')
        rect = (SDL_Rect){120, 16 * 1, 16, 16};
    if (c == 'b')
        rect = (SDL_Rect){16 * 2, 16 * 0, 16, 16};
    return rect;
}

void renderMap(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect **mapRects, char *textMap)
{
    SDL_Rect rectTexture;
    int countChar = 0;

    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 15; x++) {
            rectTexture = checkTexture(textMap[countChar]);
            SDL_RenderCopy(renderer, texture, &rectTexture, &mapRects[y][x]);
            countChar += 1;
        }
        countChar += 1;
    }
}

SDL_Rect **createMap(void)
{
    int nbMapColumns = 15;
    int nbMapLines = 11;
    int rectSize = WIDTH / 15; 
    SDL_Rect **textureMap = malloc(sizeof(SDL_Rect *) * (nbMapLines + 1));
    SDL_Rect rectPos = {0, 0, rectSize, rectSize};
    int posx = 0;
    int posy = 0;

    for (int y = 0; y < nbMapLines; y++) {
        textureMap[y] = malloc(sizeof(SDL_Rect) * (nbMapColumns + 1));
        rectPos.y = posy;
        for (int x = 0; x < nbMapColumns; x++) {
            rectPos.x = posx;
            textureMap[y][x] = rectPos;
            posx += rectSize;
        }
        posy += rectSize;
        posx = 0;
    }
    return textureMap;
}

int main(void)
{
    SDL_Window *window = NULL;
    int status = GAME;
    SDL_Renderer *renderer;
    SDL_Surface *mapTileset;
    SDL_Texture *texture;
    SDL_Rect **mapRects = createMap();
    SDL_Rect playerRect = {0, 32, 10, 16};
    SDL_Rect playerPos = {60, 50, 10 * 4, 16 * 4};
    char *textMap = readMap("./maps/map1.txt");

    window = SDL_CreateWindow("Bomberman", 0, 0, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    mapTileset = SDL_LoadBMP("./assets/bomber.bmp");
    texture = SDL_CreateTextureFromSurface(renderer, mapTileset);
    while (status != LEAVE) {
        status = eventLoop(&playerPos);
        renderMap(renderer, texture, mapRects, textMap);
        SDL_RenderCopy(renderer, texture, &playerRect, &playerPos);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(mapTileset);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
