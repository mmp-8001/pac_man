//
// Created by mmp on 1/3/2021.
//

#ifndef PAC_MAN_PACMAN_H
#define PAC_MAN_PACMAN_H

#include "SDL2/SDL.h"

//properties of pacman
typedef struct {
    int pWidth;
    int pHeight;
    int pVelocity;
    int pPosx;
    int pPosy;
} PACMAN;
//extern pacman initialization
extern void PACMAN_init(PACMAN *obj, int posX, int posY);

#endif //PAC_MAN_PACMAN_H
