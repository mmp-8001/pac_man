//
// Created by mmp on 1/11/2021.
//

#ifndef PAC_MAN_GHOST_H
#define PAC_MAN_GHOST_H

#include "SDL2/SDL.h"
#include "../main/LTexture.h"
#include "../objects/map.h"

//Properties of ghost
typedef struct {
    int gStatus;
    int gAngle;
    int gVelocity;
    int gMove;
    char gName[10];
    LTexture gTexture;
    SDL_Rect gBox;
    SDL_RendererFlip gFlipType;
} GHOST;

//Extern ghost initialization
extern void GHOST_init(GHOST *obj, int posX, int posY, char name[]);

//Extern ghost termination function
extern void GHOST_terminate(GHOST *obj);

//Extern ghost render to render ghost to window
extern void GHOST_render(GHOST *obj);

//Extern action function to make ghost alive
extern void GHOST_action(GHOST *obj);

#endif //PAC_MAN_GHOST_H