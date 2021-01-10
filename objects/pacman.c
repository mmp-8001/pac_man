//
// Created by mmp on 1/3/2021.
//

#include "pacman.h"

//Prototype for this file functions
void create_status();

//Const global variable for our pacman
const int PACMAN_WIDTH = 30;
const int PACMAN_HEIGHT = 30;
const int PACMAN_VEL = 1;
const int WALKING_ANIMATION_FRAMES = 5;
const int ANIMATION_DELAY = 5;
const int PACMAN_NEXT_MOVE = 45;
char PACMAN_PIC[] = "../assets/pacman.png";
enum PACMAN_MOVE {
    PAC_UP = SDLK_UP, PAC_DOWN = SDLK_DOWN, PAC_RIGHT = SDLK_RIGHT, PAC_LEFT = SDLK_LEFT
};

SDL_Rect PACMAN_SPRITE_CLIP[5];


//This function create one pacman
void PACMAN_init(PACMAN *obj, int posX, int posY) {
    create_status();
    obj->status = 0;
    obj->angle = 0;
    obj->pMove = PAC_RIGHT;
    obj->pVelocity = PACMAN_VEL;
    obj->pBox.x = posX;
    obj->pBox.y = posY;
    obj->pBox.w = PACMAN_WIDTH;
    obj->pBox.h = PACMAN_HEIGHT;
    obj->pFlipType = SDL_FLIP_NONE;
    LTexture_loadFromFile(&obj->pTexture, PACMAN_PIC);
}

//This function terminate pacman
void PACMAN_terminate(PACMAN *obj) {
    LTexture_free(&obj->pTexture);
}

//This function render pacman to window
void PACMAN_render(PACMAN *obj) {
    LTexture_render(&obj->pTexture, obj->pBox.x, obj->pBox.y, &PACMAN_SPRITE_CLIP[obj->status], obj->angle, NULL,
                    obj->pFlipType);
}

//This function make pacman alive
void PACMAN_action(PACMAN *obj) {
    static int frame;
    obj->status = frame / ANIMATION_DELAY;
    if (frame / ANIMATION_DELAY >= WALKING_ANIMATION_FRAMES) {
        frame = 0;
        obj->status = 0;
    }
    frame++;
}

//This function handle pacman direction and next move
void PACMAN_handle(PACMAN *obj, Tile **tileSet, SDL_Event e) {
    static int time = 0, move;

    //Get pac man velocity
    int vel = obj->pVelocity;

    //Check if user press key down
    if (e.type == SDL_KEYDOWN) {
        //Get key which user press it and set direction of our pacman
        move = e.key.keysym.sym;
    }

    //Save user direction 45 times
    if (time == PACMAN_NEXT_MOVE) {
        move = obj->pMove;
        time = 0;
    }

    //Allow pacman to move according to user keydown
    switch (move) {
        //If user press up key
        case PAC_UP:
            obj->pBox.y -= vel;
            if (obj->pBox.y < 0 || !MAP_touches(obj->pBox, tileSet)) {
                obj->pMove = PAC_UP;
                obj->angle = 270;
            }
            obj->pBox.y += vel;
            break;

            //If user press down key
        case PAC_DOWN:
            obj->pBox.y += vel;
            if (obj->pBox.y > SCREEN_HEIGHT || !MAP_touches(obj->pBox, tileSet)) {
                obj->pMove = PAC_DOWN;
                obj->angle = 90;
            }
            obj->pBox.y -= vel;
            break;

            //If user press right key
        case PAC_RIGHT:
            obj->pBox.x += vel;
            if (obj->pBox.x > SCREEN_WIDTH || !MAP_touches(obj->pBox, tileSet)) {
                obj->pMove = PAC_RIGHT;
                if (obj->angle == 180 || obj->angle == 270 || obj->angle == 90) {
                    obj->pFlipType = SDL_FLIP_NONE;
                }
                obj->angle = 0;
            }
            obj->pBox.x -= vel;
            break;

            //IF user press left key
        case PAC_LEFT:
            obj->pBox.x -= vel;
            if (obj->pBox.x < 0 || !MAP_touches(obj->pBox, tileSet)) {
                obj->pMove = PAC_LEFT;
                if (obj->angle == 0 || obj->angle == 270 || obj->angle == 90) {
                    obj->pFlipType = SDL_FLIP_VERTICAL;
                }
                obj->angle = 180;
            }
            obj->pBox.x += vel;
            break;
    }
    time++;
}

//This function move pacman according to it's direction
void PACMAN_move(PACMAN *obj, Tile **tileSet) {
    int vel = obj->pVelocity;
    switch (obj->pMove) {
        //If want to go up
        case PAC_UP:
            obj->pBox.y -= vel;
            if (obj->pBox.y < 0 || MAP_touches(obj->pBox, tileSet)) {
                obj->pBox.y += vel;
            }
            break;

            //If want to go down
        case PAC_DOWN:
            obj->pBox.y += vel;
            if (obj->pBox.y > SCREEN_HEIGHT || MAP_touches(obj->pBox, tileSet)) {
                obj->pBox.y -= vel;
            }
            break;

            //If want to go right
        case PAC_RIGHT:
            obj->pBox.x += vel;
            if (obj->pBox.x > SCREEN_WIDTH || MAP_touches(obj->pBox, tileSet)) {
                obj->pBox.x -= vel;
            }
            break;

            //If want to go left
        case PAC_LEFT:
            obj->pBox.x -= vel;
            if (obj->pBox.x < 0 || MAP_touches(obj->pBox, tileSet)) {
                obj->pBox.x += vel;
            }
            break;
    }
}

//This function create different status of pacman
void create_status() {
    //Status 0
    PACMAN_SPRITE_CLIP[0].x = 0;
    PACMAN_SPRITE_CLIP[0].y = 0;
    PACMAN_SPRITE_CLIP[0].w = 30;
    PACMAN_SPRITE_CLIP[0].h = 30;

    //Status 1
    PACMAN_SPRITE_CLIP[1].x = 30;
    PACMAN_SPRITE_CLIP[1].y = 0;
    PACMAN_SPRITE_CLIP[1].w = 30;
    PACMAN_SPRITE_CLIP[1].h = 30;

    //Status 2
    PACMAN_SPRITE_CLIP[2].x = 60;
    PACMAN_SPRITE_CLIP[2].y = 0;
    PACMAN_SPRITE_CLIP[2].w = 30;
    PACMAN_SPRITE_CLIP[2].h = 30;

    //Status 3
    PACMAN_SPRITE_CLIP[3].x = 90;
    PACMAN_SPRITE_CLIP[3].y = 0;
    PACMAN_SPRITE_CLIP[3].w = 30;
    PACMAN_SPRITE_CLIP[3].h = 30;

    //Status 4
    PACMAN_SPRITE_CLIP[4].x = 120;
    PACMAN_SPRITE_CLIP[4].y = 0;
    PACMAN_SPRITE_CLIP[4].w = 30;
    PACMAN_SPRITE_CLIP[4].h = 30;
}