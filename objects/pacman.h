//
// Created by mmp on 1/3/2021.
//

#ifndef PAC_MAN_PACMAN_H
#define PAC_MAN_PACMAN_H

#include "../common/pac_common.h"
#include "../main/texture.h"
#include "../objects/map.h"

//Properties of pacman
typedef struct {
    int pStatus;
    int pAngle;
    int pVelocity;
    int pMove;
    TEXTURE pTexture;
    SDL_Rect pBox;
    SDL_RendererFlip pFlipType;
} PACMAN;

//Extern pacman initialization
extern void PACMAN_init(PACMAN *obj, int posX, int posY);

//Extern pacman termination function
extern void PACMAN_terminate(PACMAN *obj);

//Extern pacman render to render pacman to window
extern void PACMAN_render(PACMAN *obj);

//Extern action function to make pacman alive
extern void PACMAN_action(PACMAN *obj);

//Extern pacman handle to handle direction and next move of pacman
extern void PACMAN_handle(PACMAN *obj, Tile ***tileSet, SDL_Event e);

//Extern pacman move to move pacman according to it's direction
extern void PACMAN_move(PACMAN *obj, Tile ***tileSet);

#endif //PAC_MAN_PACMAN_H