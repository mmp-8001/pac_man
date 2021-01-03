#include <stdio.h>
#include <SDL2/SDL.h>
#include "objects/pacman.h"

int main(int argc, char *argv[]) {
    PACMAN pacMan;
    PACMAN_init(&pacMan, 10, 10);
    SDL_Init(SDL_INIT_VIDEO);
    printf("we are going to create Pac-Man!\n");
    printf("now we have our pacman with width = %d; height = %d; velocity = %d; posX = %d; posY = %d", pacMan.pWidth,
           pacMan.pHeight, pacMan.pVelocity,
           pacMan.pPosy, pacMan.pPosx);

    return 0;
}
