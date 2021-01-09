//
// Created by mmp on 1/5/2021.
//

#include "map.h"

//Prototype for this file functions
void create_tile();

void tile_render(Tile *obj);

//Global variable for this file
int TILE_WIDTH = 30;
int TILE_HEIGHT = 30;
short int TILE_WALL = 0;
short int TILE_TRANS = 1;
short int TILE_SEED = 2;
int TOTAL_TILES = 400;
char TILES_PIC[] = "../assets/tiles.png";
SDL_Rect gTileClips[3];
LTexture gTileTexture;

//Temporary map for testing
int map[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0,
             0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
             0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0,
             0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
             0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0,
             0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
             0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0,
             0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
             0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0,
};

//This function initialize map
Tile **MAP_init() {
    //Calculate total tiles according to screen width and screen height
    int tile_type, x = 0, y = 0;

    //Allocate proper pointers, effectively an array
    Tile **tileSet = malloc(TOTAL_TILES * sizeof(struct Tile *));

    //If memory allocated wasn't successful
    if (tileSet == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }

    //Initialize tiles value
    for (int i = 0; i < TOTAL_TILES; ++i) {
        tile_type = map[i];
        tileSet[i] = malloc(sizeof(Tile));
        tileSet[i]->mType = tile_type;
        tileSet[i]->mBox.x = x;
        tileSet[i]->mBox.y = y;
        tileSet[i]->mBox.w = TILE_WIDTH;
        tileSet[i]->mBox.h = TILE_HEIGHT;
        x += TILE_WIDTH;

        //If we've gone too far
        if (x >= SCREEN_WIDTH) {
            //Move back
            x = 0;

            //Move to the next row
            y += TILE_HEIGHT;
        }
    }

    //Load tiles pic and proper clip array
    create_tile();
    return tileSet;
}

//This function Load tile texture and clip that texture to gain proper section
void create_tile() {
    //Load tile texture
    if (!LTexture_loadFromFile(&gTileTexture, TILES_PIC)) {
        printf("Failed to load tile set texture!\n");
        exit(0);
    }

    //Specified wall section in pic
    gTileClips[TILE_WALL].x = 0;
    gTileClips[TILE_WALL].y = 0;
    gTileClips[TILE_WALL].w = TILE_WIDTH;
    gTileClips[TILE_WALL].h = TILE_HEIGHT;

    //Specified seed section in pic
    gTileClips[TILE_SEED].x = 30;
    gTileClips[TILE_SEED].y = 0;
    gTileClips[TILE_SEED].w = TILE_WIDTH;
    gTileClips[TILE_SEED].h = TILE_HEIGHT;

    //Specified transparent section in pic
    gTileClips[TILE_TRANS].x = 60;
    gTileClips[TILE_TRANS].y = 0;
    gTileClips[TILE_TRANS].w = TILE_WIDTH;
    gTileClips[TILE_TRANS].h = TILE_HEIGHT;
}

//This function render map to window
void MAP_render(Tile **tileSet) {
    for (int i = 0; i < TOTAL_TILES; ++i) {
        tile_render(tileSet[i]);
    }
}

//this function render tile to window
void tile_render(Tile *obj) {
    LTexture_render(&gTileTexture, obj->mBox.x, obj->mBox.y, &gTileClips[obj->mType], 0.0, NULL, SDL_FLIP_NONE);
}