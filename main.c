#include "common/pac_common.h"
#include "objects/pacman.h"
#include "objects/map.h"
#include "objects/ghost.h"

int main(int argc, char *argv[]) {
    if (!app_init()) {
        printf("Failed to initialize the app!\n");
        return 1;
    }
    //Main loop flag
    bool quit = false;

    //Pause flag
    bool pause = false;

    //Create map
    Tile ***tileSet = MAP_init();

    //Event handler
    SDL_Event e;

    //Create pacman
    PACMAN pacMan;
    PACMAN_init(&pacMan, 30, 30);

    //Create ghosts
    GHOST pinky;
    GHOST_init(&pinky, 0, 30, "PINKY");

    //Main loop, While application is running
    while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    pause = pause ? false : true;
                }
            }
        }
        if (!pause) {
            //Pacman logic
            PACMAN_handle(&pacMan, tileSet, e);
            PACMAN_action(&pacMan);
            PACMAN_move(&pacMan, tileSet);

            //Ghosts logic
            GHOST_action(&pinky);
        }

        //Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(gRenderer);

        //Render map
        MAP_render(tileSet);

        //Render pacman to window
        PACMAN_render(&pacMan);

        //Render ghosts
        GHOST_render(&pinky);

        //Control speed of app
        SDL_Delay(APP_DELAY);

        //Update screen
        SDL_RenderPresent(gRenderer);
    }

    //Destroy all objects in app
    PACMAN_terminate(&pacMan);
    GHOST_terminate(&pinky);
    MAP_terminate(tileSet);
    app_close();

    return 0;
}