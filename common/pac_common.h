//
// Created by mmp on 1/3/2021.
//

#ifndef PAC_MAN_PAC_COMMON_H
#define PAC_MAN_PAC_COMMON_H

#include <stdio.h>
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

//variable which want to use across all files
extern const char gAppName[];
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;

extern bool app_init();

#endif //PAC_MAN_PAC_COMMON_H
