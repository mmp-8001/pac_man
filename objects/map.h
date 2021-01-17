//
// Created by mmp on 1/5/2021.
//

#ifndef PAC_MAN_MAP_H
#define PAC_MAN_MAP_H

#include "../common/pac_common.h"
#include "../main/LTexture.h"

typedef enum {
    TILE_WALL_PARALLEL,
    TILE_TRANS,
    TILE_SEED,
    TILE_WALL_ROUND,
    TILE_WALL_CUBE,
    TILE_WALL_LINE,
    TILE_WALL_CORNER,
    TILE_WALL_EMPTY
} TILE_TYPE;

//Properties of tile
typedef struct {
    SDL_Rect mBox;
    TILE_TYPE mType;
    int mAngle;
} Tile;

//Extern map init to create one map
extern Tile ***MAP_init();

//Extern map render to render map to window
extern void MAP_render(Tile ***tileSet);

//Extern map touches to check if an object touch map's components
extern bool MAP_touches(SDL_Rect box, Tile ***tiles);

extern void MAP_terminate(Tile ***tileSet);

#endif //PAC_MAN_MAP_H