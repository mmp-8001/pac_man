#include "common/pac_common.h"
#include "objects/pacman.h"
#include "objects/map.h"

int main(int argc, char *argv[]) {
    if (!app_init()) {
        printf("Failed to initialize the app!\n");
        return 1;
    }
    //Main loop flag
    bool quit = false;

    //Create map
    Tile **tileSet = MAP_init();

    //Event handler
    SDL_Event e;
    //Create pacman
    PACMAN pacMan;
    PACMAN_init(&pacMan, 0, 32);

    //Main loop, While application is running
    while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            PACMAN_handle(&pacMan, tileSet, e);
        }
        //Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(gRenderer);

        //Render map
        MAP_render(tileSet);

        //Animate pacman
        PACMAN_action(&pacMan);
        //Move pacman
        PACMAN_move(&pacMan, tileSet);
        //Render pacman to window
        PACMAN_render(&pacMan);

        //Update screen
        SDL_RenderPresent(gRenderer);
    }

    PACMAN_terminate(&pacMan);
    free(tileSet);
    app_close();

    return 0;
}