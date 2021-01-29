//
// Created by mmp on 1/11/2021.
//

#ifndef PAC_MAN_GHOST_H
#define PAC_MAN_GHOST_H

#include "SDL2/SDL.h"
#include "../main/LTexture.h"
#include "../objects/map.h"
#include "pacman.h"

//Properties of ghost
typedef struct {
    int gStatus;
    int gVelocity;
    int gMove;
    int gMood;
    char gName[10];
    LTexture gTexture;
    SDL_Rect gBox;
} GHOST;

//Extern ghost initialization
extern void GHOST_init(GHOST *obj, int posX, int posY, char name[]);

//Extern ghost termination function
extern void GHOST_terminate(GHOST *obj);

//Extern ghost render to render ghost to window
extern void GHOST_render(GHOST *obj);

//Extern ghost action function to make ghost alive
extern void GHOST_action(GHOST *obj);

//Extern ghost move to implement ghosts AI
extern void GHOST_move(GHOST *gObj, PACMAN *pObj, Tile ***tileSet, GHOST blinky);

#endif //PAC_MAN_GHOST_H