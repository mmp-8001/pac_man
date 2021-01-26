//
// Created by mmp on 1/11/2021.
//

#include "ghost.h"

//Prototype for this file functions
static void create_status();

static bool proper_pic(char pic[], char name[]);

//Const global variable for our pacman
static const int GHOST_WIDTH = 30;
static const int GHOST_HEIGHT = 30;
static const int GHOST_VEL = 1;
static const int WALKING_ANIMATION_FRAMES = 2;
static const int ANIMATION_DELAY = 60;
static SDL_Rect GHOST_SPRITE_CLIP[8];
enum GHOST_face {
    G_F_UP = 0, G_F_RIGHT = 2, G_F_DOWN = 4, G_F_LEFT = 6
};
enum GHOST_move {
    G_UP, G_RIGHT, G_DOWN, G_LEFT
};

//This function create one ghost
extern void GHOST_init(GHOST *obj, int posX, int posY, char name[]) {
    char pic[30];
    //Get proper pic path according to ghost's name
    if (!proper_pic(pic, name)) {
        printf("Cannot find specified ghost");
        exit(25);
    }

    create_status();
    obj->gStatus = 0;
    obj->gMove = G_RIGHT;
    obj->gVelocity = GHOST_VEL;
    obj->gBox.x = posX;
    obj->gBox.y = posY;
    obj->gBox.w = GHOST_WIDTH;
    obj->gBox.h = GHOST_HEIGHT;
    strcpy(obj->gName, name);
    obj->gTexture.mTexture = NULL;
    obj->gTexture.mHeight = 0;
    obj->gTexture.mWidth = 0;
    LTexture_loadFromFile(&obj->gTexture, pic);
}

//This function get proper pic path according to ghost's name
static bool proper_pic(char pic[], char name[]) {
    if (strcmp(name, "PINKY") == 0)strcpy(pic, "../assets/pinky.png");
    else if (strcmp(name, "CLYDE") == 0)strcpy(pic, "../assets/clyde.png");
    else if (strcmp(name, "BLINKY") == 0)strcpy(pic, "../assets/blinky.png");
    else if (strcmp(name, "INKY") == 0)strcpy(pic, "../assets/inky.png");
    else return false;
    return true;
}

//This function terminate ghost
extern void GHOST_terminate(GHOST *obj) {
    LTexture_free(&obj->gTexture);
    obj = NULL;
}

//This function render ghost to window
extern void GHOST_render(GHOST *obj) {
    LTexture_render(&obj->gTexture, obj->gBox.x, obj->gBox.y, &GHOST_SPRITE_CLIP[obj->gStatus], 0.0, NULL,
                    SDL_FLIP_NONE);
}

//This function make ghost alive
extern void GHOST_action(GHOST *obj) {
    static int frame, state;

    //Check which direction the ghost go and face it to that direction
    if (obj->gMove == G_UP)obj->gStatus = G_F_UP + state;
    else if (obj->gMove == G_RIGHT)obj->gStatus = G_F_RIGHT + state;
    else if (obj->gMove == G_DOWN)obj->gStatus = G_F_DOWN + state;
    else if (obj->gMove == G_LEFT)obj->gStatus = G_F_LEFT + state;

    //Get proper animation delay
    state = frame / (ANIMATION_DELAY + 1);
    if (frame / ANIMATION_DELAY >= WALKING_ANIMATION_FRAMES) {
        frame = 0;
    }
    frame++;
}

//This function create different status of ghost
static void create_status() {
    //Status 0 face up state 0
    GHOST_SPRITE_CLIP[0].x = 0;
    GHOST_SPRITE_CLIP[0].y = 0;
    GHOST_SPRITE_CLIP[0].w = 30;
    GHOST_SPRITE_CLIP[0].h = 30;

    //Status 1 face up state 1
    GHOST_SPRITE_CLIP[1].x = 30;
    GHOST_SPRITE_CLIP[1].y = 0;
    GHOST_SPRITE_CLIP[1].w = 30;
    GHOST_SPRITE_CLIP[1].h = 30;

    //Status 2 face right state 0
    GHOST_SPRITE_CLIP[2].x = 0;
    GHOST_SPRITE_CLIP[2].y = 30;
    GHOST_SPRITE_CLIP[2].w = 30;
    GHOST_SPRITE_CLIP[2].h = 30;

    //Status 3 face right state 1
    GHOST_SPRITE_CLIP[3].x = 30;
    GHOST_SPRITE_CLIP[3].y = 30;
    GHOST_SPRITE_CLIP[3].w = 30;
    GHOST_SPRITE_CLIP[3].h = 30;

    //Status 4 face down state 0
    GHOST_SPRITE_CLIP[4].x = 0;
    GHOST_SPRITE_CLIP[4].y = 60;
    GHOST_SPRITE_CLIP[4].w = 30;
    GHOST_SPRITE_CLIP[4].h = 30;

    //Status 5 face down state 1
    GHOST_SPRITE_CLIP[5].x = 30;
    GHOST_SPRITE_CLIP[5].y = 60;
    GHOST_SPRITE_CLIP[5].w = 30;
    GHOST_SPRITE_CLIP[5].h = 30;

    //Status 6 face left state 0
    GHOST_SPRITE_CLIP[6].x = 0;
    GHOST_SPRITE_CLIP[6].y = 90;
    GHOST_SPRITE_CLIP[6].w = 30;
    GHOST_SPRITE_CLIP[6].h = 30;

    //Status 7 face left state 1
    GHOST_SPRITE_CLIP[7].x = 30;
    GHOST_SPRITE_CLIP[7].y = 90;
    GHOST_SPRITE_CLIP[7].w = 30;
    GHOST_SPRITE_CLIP[7].h = 30;
}