//
// Created by mmp on 1/3/2021.
//

#include "pacman.h"

//const global variable for our pacman
const int PACMAN_WIDTH = 30;
const int PACMAN_HEIGHT = 30;
const int PACMAN_VEL = 10;

//this function create one pacman
void PACMAN_init(PACMAN *obj, int posX, int posY) {
    obj->pWidth = PACMAN_WIDTH;
    obj->pHeight = PACMAN_HEIGHT;
    obj->pVelocity = PACMAN_VEL;
    obj->pPosx = posX;
    obj->pPosy = posY;
}