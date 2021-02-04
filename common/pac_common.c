//
// Created by mmp on 1/3/2021.
//

#include "pac_common.h"

//Functions prototype
static bool load_font();

//The name of our app
const char gAppName[] = "PAC-MAN";

//Screen dimension constants
const int SCREEN_WIDTH = 690;
const int SCREEN_HEIGHT = 720;

//Control app speed
const int APP_DELAY = 10;

//Pacman life
int PACMAN_LIFE = 3;

//Score
int GAME_SCORE = 0;
int GAME_CURRENT_SCORE = 0;

//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The window renderer
SDL_Renderer *gRenderer = NULL;

//Font variables
TTF_Font *gFont = NULL;
static char *FONT_PATH = "../assets/ARCADE_R.ttf";
SDL_Color gTextColor = {255, 255, 255};

//Button color
SDL_Color BUTTON_ON_HOVER_COLOR = {255, 255, 255};
SDL_Color BUTTON_COLOR = {100, 100, 100};

//This function check lib, init SDL and SDL_Image, create renderer and window
extern bool app_init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }

        //Create window
        gWindow = SDL_CreateWindow(gAppName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }

                //Initialize SDL_mixer
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                    success = false;
                }

                //Initialize SDL_ttf
                if (TTF_Init() == -1) {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }
            }
        }
    }

    //Load font
    if (!load_font()) success = false;

    return success;
}

//This function close our application
extern void app_close() {
    //Destroy window
    SDL_DestroyWindow(gWindow);
    //Destroy renderer
    SDL_DestroyRenderer(gRenderer);
    //Destroy loaded font
    TTF_CloseFont(gFont);
    gWindow = NULL;
    gRenderer = NULL;
    gFont = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
    TTF_Quit();
}

//This function load font
static bool load_font() {
    //Open the font
    gFont = TTF_OpenFont(FONT_PATH, 15);
    if (gFont == NULL) {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    return true;
}