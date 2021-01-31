//
// Created by mmp on 1/3/2021.
//

#ifndef PAC_MAN_PAC_COMMON_H
#define PAC_MAN_PAC_COMMON_H

#include <stdio.h>
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include "../main/LTexture.h"

//Variable which want to use across all files
extern const char gAppName[];
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int APP_DELAY;
extern const int INTRO_TEXT_FADE_TIME;
extern const int INTRO_PIC_FADE_TIME;
extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;
extern TTF_Font *gFont;
extern SDL_Color gTextColor;

//Extern app init to initialize our app
extern bool app_init();

//Extern app close to close our app
extern void app_close();

#endif //PAC_MAN_PAC_COMMON_H