//
// Created by mmp on 1/5/2021.
//

#ifndef PAC_MAN_MAP_H
#define PAC_MAN_MAP_H

#include "../common/pac_common.h"
#include "../main/LTexture.h"

//Properties of tile
typedef struct {
    SDL_Rect mBox;
    int mType;
} Tile;

//Extern map init to create one map
extern Tile **MAP_init();

//Extern map render to render map to window
extern void MAP_render(Tile **tileSet);

//Extern map touches to check if an object touch map's components
extern bool MAP_touches(SDL_Rect box, Tile *tiles[]);

#endif //PAC_MAN_MAP_H