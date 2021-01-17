//
// Created by mmp on 1/11/2021.
//

#include "ghost.h"

static void create_status();

//Const global variable for our pacman
static const int GHOST_WIDTH = 30;
static const int GHOST_HEIGHT = 30;
static const int GHOST_VEL = 1;
static const int WALKING_ANIMATION_FRAMES = 2;
static const int ANIMATION_DELAY = 15;
static char GHOST_PIC[] = "../assets/ghost.png";

static SDL_Rect GHOST_SPRITE_CLIP[5];

//This function create one ghost
extern void GHOST_init(GHOST *obj, int posX, int posY, char name[]) {
    create_status();
    obj->gStatus = 0;
    obj->gAngle = 0;
    obj->gMove = 1;
    obj->gVelocity = GHOST_VEL;
    obj->gBox.x = posX;
    obj->gBox.y = posY;
    obj->gBox.w = GHOST_WIDTH;
    obj->gBox.h = GHOST_HEIGHT;
    strcpy(obj->gName, name);
    obj->gFlipType = SDL_FLIP_NONE;
    LTexture_loadFromFile(&obj->gTexture, GHOST_PIC);
}

//This function terminate ghost
extern void GHOST_terminate(GHOST *obj) {
    LTexture_free(&obj->gTexture);
    obj = NULL;
}

//This function render ghost to window
extern void GHOST_render(GHOST *obj) {
    LTexture_render(&obj->gTexture, obj->gBox.x, obj->gBox.y, &GHOST_SPRITE_CLIP[obj->gStatus], obj->gAngle, NULL,
                    obj->gFlipType);
}

//This function make ghost alive
extern void GHOST_action(GHOST *obj) {
    static int frame;
    obj->gStatus = frame / ANIMATION_DELAY;
    if (frame / ANIMATION_DELAY >= WALKING_ANIMATION_FRAMES) {
        frame = 0;
        obj->gStatus = 0;
    }
    frame++;
}

//This function create different status of ghost
static void create_status() {
    //Status 0
    GHOST_SPRITE_CLIP[0].x = 0;
    GHOST_SPRITE_CLIP[0].y = 0;
    GHOST_SPRITE_CLIP[0].w = 30;
    GHOST_SPRITE_CLIP[0].h = 30;

    //Status 1
    GHOST_SPRITE_CLIP[1].x = 30;
    GHOST_SPRITE_CLIP[1].y = 0;
    GHOST_SPRITE_CLIP[1].w = 30;
    GHOST_SPRITE_CLIP[1].h = 30;
}