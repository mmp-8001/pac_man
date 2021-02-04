#include "common/pac_common.h"
#include "objects/pacman.h"
#include "objects/ghost.h"
#include "objects/button.h"

//Define game status
typedef enum {
    PAUSED_STATE, QUIT_STATE, RESTART, KILLED, PLAYING, QUIT
} GAME_STATUS;


//Prototype of our functions
void start_game();

void start_intro(TEXTURE *intro, TEXTURE *textTexture, SDL_Event e);

void pause_load(TEXTURE *paused_text, TEXTURE *quit_text);

void pause(TEXTURE *paused_text, TEXTURE *quit_text, BUTTON *resume_box, BUTTON *quit_box, BUTTON *yes_box,
           BUTTON *no_box, SDL_Event *e, GAME_STATUS *game_status);

int get_center_x(int w);

int get_center_y(int h);

int main(int argc, char *argv[]) {
    //Init app and check dependencies
    if (!app_init()) {
        printf("Failed to initialize the app!\n");
        return 1;
    }
    //Start game
    start_game();

    //Close game and destroy objects
    app_close();

    return 0;
}

void start_game() {
    //Main loop flag
    GAME_STATUS status = RESTART;

    //Event handler
    SDL_Event e;

    //Introduction section
    TEXTURE intro, textTexture;
    TEXTURE_init(2, &intro, &textTexture);
    start_intro(&intro, &textTexture, e);

    //Pause section
    TEXTURE paused_text, quit_text;
    TEXTURE_init(2, &paused_text, &quit_text);
    BUTTON resume_box, quit_box, yes_box, no_box;
    if (!BUTTON_init(&resume_box, "RESUME"))status = QUIT;
    if (!BUTTON_init(&quit_box, "QUIT"))status = QUIT;
    if (!BUTTON_init(&yes_box, "YES"))status = QUIT;
    if (!BUTTON_init(&no_box, "NO"))status = QUIT;
    pause_load(&paused_text, &quit_text);

    //Heart loaded section
    TEXTURE heart;
    TEXTURE_init(1, &heart);
    TEXTURE_loadFromFile(&heart, "../assets/heart.png");

    while (status == RESTART) {
        //Create map
        Tile ***tileSet = MAP_init();

        status = KILLED;

        while (status == KILLED) {
            //Create pacman
            PACMAN pacMan;
            PACMAN_init(&pacMan, 150, 90);

            //Create ghosts
            GHOST pinky;
            GHOST_init(&pinky, 30, 90, "PINKY");
            GHOST blinky;
            GHOST_init(&blinky, 330, 300, "BLINKY");
            GHOST inky;
            GHOST_init(&inky, 510, 480, "INKY");
            GHOST clyde;
            GHOST_init(&clyde, 30, 480, "CLYDE");

            status = PLAYING;

            //Main loop, While application is running
            while (status == PLAYING) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_QUIT) {
                        status = QUIT;
                    }
                    if (e.type == SDL_KEYDOWN) {
                        if (e.key.keysym.sym == SDLK_ESCAPE) {
                            status = PAUSED_STATE;
                            pause(&paused_text, &quit_text, &resume_box, &quit_box, &yes_box, &no_box, &e, &status);
                        }
                    }
                }
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

                //Render pacman life
                MAP_life_render(&heart);

                //Control speed of app
                SDL_Delay(APP_DELAY);

                //Update screen
                SDL_RenderPresent(gRenderer);

                if (PACMAN_killed(&pacMan, tileSet, pinky.gBox, inky.gBox, clyde.gBox, blinky.gBox))status = KILLED;
                if (PACMAN_LIFE == 0)status = RESTART;
            }

            //Destroy all objects in app
            PACMAN_terminate(&pacMan);
            GHOST_terminate(&pinky);
            GHOST_terminate(&blinky);
            GHOST_terminate(&inky);
            GHOST_terminate(&clyde);
        }
        MAP_terminate(tileSet);
    }
    TEXTURE_free(&intro);
    TEXTURE_free(&textTexture);
    TEXTURE_free(&paused_text);
    TEXTURE_free(&quit_text);
    BUTTON_terminate(&resume_box);
    BUTTON_terminate(&quit_box);
    BUTTON_terminate(&yes_box);
    BUTTON_terminate(&no_box);
    TEXTURE_free(&heart);
}

//Implement start section of game
void start_intro(TEXTURE *intro, TEXTURE *textTexture, SDL_Event e) {
    int intro_alpha = 0, text_alpha = 80, counter = 4;
    bool start = false;

    //Render text
    if (!TEXTURE_FromRenderedText(textTexture, "PRESS ANY KEY TO START", gTextColor)) {
        printf("Failed to render text texture!\n");
        start = true;
    }

    //Load introduction picture
    if (!TEXTURE_loadFromFile(intro, "../assets/intro.png")) {
        printf("Failed to load introduction image!\n");
        start = true;
    }

    while (!start) {
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                //Destroy texture
                TEXTURE_free(intro);
                TEXTURE_free(textTexture);
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
        TEXTURE_set_alpha(intro, intro_alpha);
        TEXTURE_render(intro, SCREEN_WIDTH / 2 - intro->mWidth / 2, SCREEN_HEIGHT / 2 - intro->mHeight / 2, NULL, 0.0,
                       NULL, SDL_FLIP_NONE);


        TEXTURE_set_alpha(textTexture, text_alpha);
        TEXTURE_render(textTexture, SCREEN_WIDTH / 2 - textTexture->mWidth / 2, SCREEN_HEIGHT / 2 + intro->mHeight,
                       NULL,
                       0.0,
                       NULL, SDL_FLIP_NONE);

        //Faded animation simulation
        if (intro_alpha < 255) intro_alpha++;

        //Make text blinking
        if (text_alpha >= 253) counter = -2;
        if (text_alpha <= 80) counter = 2;
        text_alpha += counter;

        //Control faded animation speed
        SDL_Delay(APP_DELAY);

        //Update screen
        SDL_RenderPresent(gRenderer);
    }
}

//Load what we want for pause sexrion
void pause_load(TEXTURE *paused_text, TEXTURE *quit_text) {
    //Render paused text
    if (!TEXTURE_FromRenderedText(paused_text, "PAUSED", gTextColor)) {
        printf("Failed to render text texture!\n");
        exit(1);
    }
    //Render quit text
    if (!TEXTURE_FromRenderedText(quit_text, "QUIT GAME?", gTextColor)) {
        printf("Failed to render text texture!\n");
        exit(1);
    }
}

//Implement pause section of game
void pause(TEXTURE *paused_text, TEXTURE *quit_text, BUTTON *resume_box, BUTTON *quit_box, BUTTON *yes_box,
           BUTTON *no_box, SDL_Event *e, GAME_STATUS *game_status) {
    //Main loop for pause section
    while (*game_status == PAUSED_STATE || *game_status == QUIT_STATE) {
        //Handle events
        while (SDL_PollEvent(e) != 0) {
            //User requests quit
            if (e->type == SDL_QUIT) {
                *game_status = QUIT;
            }
            //If user press escape resume game
            if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE) {
                *game_status = PLAYING;
            }
            //If we were in paused state
            if (*game_status == PAUSED_STATE) {
                //Handle state of button
                BUTTON_handle(resume_box, e);
                BUTTON_handle(quit_box, e);

                //Change color if hover or not
                if (quit_box->state == BUTTON_MOUSE_OVER) BUTTON_hover(quit_box);
                else BUTTON_not_hover(quit_box);
                if (resume_box->state == BUTTON_MOUSE_OVER) BUTTON_hover(resume_box);
                else BUTTON_not_hover(resume_box);

                //Change state if click on each button
                if (quit_box->state == BUTTON_MOUSE_UP) *game_status = QUIT_STATE;
                else if (resume_box->state == BUTTON_MOUSE_UP)*game_status = PLAYING;
            } else if (*game_status == QUIT_STATE) {
                //Handle state of button
                BUTTON_handle(no_box, e);
                BUTTON_handle(yes_box, e);

                //Change color if hover or not
                if (yes_box->state == BUTTON_MOUSE_OVER) BUTTON_hover(yes_box);
                else BUTTON_not_hover(yes_box);
                if (no_box->state == BUTTON_MOUSE_OVER) BUTTON_hover(no_box);
                else BUTTON_not_hover(no_box);
                //Change state if click on each button
                if (yes_box->state == BUTTON_MOUSE_UP) *game_status = QUIT;
                else if (no_box->state == BUTTON_MOUSE_UP) *game_status = PAUSED_STATE;
            }
        }
        //If we were in pause state
        if (*game_status == PAUSED_STATE) {
            //Clear screen
            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
            SDL_RenderClear(gRenderer);

            //Render text
            TEXTURE_render_ord(paused_text, get_center_x(paused_text->mWidth),
                               get_center_y(paused_text->mHeight) - 75);

            //Render buttons
            BUTTON_set_position(resume_box, get_center_x(resume_box->bBox.w), get_center_y(resume_box->bBox.h));
            BUTTON_render(resume_box);

            BUTTON_set_position(quit_box, get_center_x(quit_box->bBox.w), get_center_y(quit_box->bBox.h) + 75);
            BUTTON_render(quit_box);
        } else if (*game_status == QUIT_STATE) {
            //Clear screen
            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
            SDL_RenderClear(gRenderer);

            //Render text
            TEXTURE_render_ord(quit_text, get_center_x(quit_text->mWidth), get_center_y(quit_text->mHeight) - 75);

            //Render buttons
            BUTTON_set_position(yes_box, get_center_x(yes_box->bBox.w), get_center_y(yes_box->bBox.h));
            BUTTON_render(yes_box);
            BUTTON_set_position(no_box, get_center_x(no_box->bBox.w), get_center_y(no_box->bBox.h) + 75);
            BUTTON_render(no_box);
        }
        //Control faded animation speed
        SDL_Delay(APP_DELAY);

        //Update screen
        SDL_RenderPresent(gRenderer);
    }
}

//Place object in center of x axis
int get_center_x(int w) {
    return (int) (SCREEN_WIDTH / 2 - w / 2);
}

//Place object in center of y axis
int get_center_y(int h) {
    return (int) (SCREEN_HEIGHT / 2 - h / 2);
}