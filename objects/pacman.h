//
// Created by mmp on 1/3/2021.
//

#ifndef PAC_MAN_PACMAN_H
#define PAC_MAN_PACMAN_H

#include "SDL2/SDL.h"
#include "../main/LTexture.h"

//Properties of pacman
typedef struct {
    int status;
    int angle;
    int pWidth;
    int pHeight;
    int pVelocity;
    int pPosx;
    int pPosy;
    SDL_RendererFlip pFlipType;
    LTexture pTexture;
} PACMAN;

//Extern pacman initialization
extern void PACMAN_init(PACMAN *obj, int posX, int posY);

//Extern pacman termination function
extern void PACMAN_terminate(PACMAN *obj);

//Extern pacman render to render pacman to window
extern void PACMAN_render(PACMAN *obj);

//Extern action function to make pacman alive
extern void PACMAN_action(PACMAN *obj);

//Extern pacman handle to handle direction of pacman
extern void PACMAN_handle(PACMAN *obj, SDL_Event e);

#endif //PAC_MAN_PACMAN_H