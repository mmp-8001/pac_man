#include "common/pac_common.h"
#include "objects/pacman.h"
#include "objects/map.h"
#include "objects/ghost.h"
#include "SDL_draw.h"


void start_intro(LTexture *intro, LTexture *textTexture, SDL_Event e);

int main(int argc, char *argv[]) {
    if (!app_init()) {
        printf("Failed to initialize the app!\n");
        return 1;
    }
    //Main loop flag
    bool quit = false;

    //Pause flag
    bool pause = true;

    //Create map
    Tile ***tileSet = MAP_init();

    //Event handler
    SDL_Event e;

    //Introduction section
    LTexture intro, textTexture;
    start_intro(&intro, &textTexture, e);

    //Create pacman
    PACMAN pacMan;
    PACMAN_init(&pacMan, 30, 90);

    //Create ghosts
    GHOST pinky;
    GHOST_init(&pinky, 30, 90, "PINKY");
    GHOST blinky;
    GHOST_init(&blinky, 330, 300, "BLINKY");
    GHOST inky;
    GHOST_init(&inky, 510, 480, "INKY");
    GHOST clyde;
    GHOST_init(&clyde, 30, 480, "CLYDE");

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
            GHOST_move(&pinky, &pacMan, tileSet, blinky);
            GHOST_action(&blinky);
            GHOST_move(&blinky, &pacMan, tileSet, blinky);
            GHOST_action(&inky);
            GHOST_move(&inky, &pacMan, tileSet, blinky);
            GHOST_action(&clyde);
            GHOST_move(&clyde, &pacMan, tileSet, blinky);
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
        GHOST_render(&blinky);
        GHOST_render(&inky);
        GHOST_render(&clyde);

        //Control speed of app
        SDL_Delay(APP_DELAY);

        //Update screen
        SDL_RenderPresent(gRenderer);
    }

    //Destroy all objects in app
    PACMAN_terminate(&pacMan);
    GHOST_terminate(&pinky);
    GHOST_terminate(&blinky);
    GHOST_terminate(&inky);
    GHOST_terminate(&clyde);
    MAP_terminate(tileSet);
    app_close();

    return 0;
}

void start_intro(LTexture *intro, LTexture *textTexture, SDL_Event e) {
    int intro_alpha = 0, text_alpha = 80, counter;
    bool start = false;

    //Render text
    if (!LTexture_FromRenderedText(textTexture, "PRESS ANY KEY TO START", gTextColor)) {
        printf("Failed to render text texture!\n");
        exit(1);
    }

    //Load introduction picture
    if (!LTexture_loadFromFile(intro, "../assets/intro.png")) {
        printf("Failed to load introduction image!\n");
        exit(1);
    }

    while (!start) {
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                exit(0);
            }
            //If user press any key start game
            if (e.type == SDL_KEYDOWN) {
                start = true;
            }
        }

        //Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(gRenderer);

        //Set alpha and render intro pic
        LTexture_set_alpha(intro, intro_alpha);
        LTexture_render(intro, SCREEN_WIDTH / 2 - intro->mWidth / 2, SCREEN_HEIGHT / 2 - intro->mHeight / 2, NULL, 0.0,
                        NULL, SDL_FLIP_NONE);


        LTexture_set_alpha(textTexture, text_alpha);
        LTexture_render(textTexture, SCREEN_WIDTH / 2 - textTexture->mWidth / 2, SCREEN_HEIGHT / 2 + intro->mHeight,
                        NULL,
                        0.0,
                        NULL, SDL_FLIP_NONE);

        //Faded animation simulation
        if (intro_alpha < 255 - INTRO_PIC_FADE_TIME) intro_alpha += INTRO_PIC_FADE_TIME;

        //Make text blinking
        if (text_alpha >= 255 - INTRO_TEXT_FADE_TIME) counter = -INTRO_TEXT_FADE_TIME;
        if (text_alpha <= 80) counter = INTRO_TEXT_FADE_TIME;
        text_alpha += counter;

        //Control faded animation speed
        SDL_Delay(APP_DELAY);

        //Update screen
        SDL_RenderPresent(gRenderer);
    }

    //Destroy texture
    LTexture_free(intro);
    LTexture_free(textTexture);
}