//
// Created by mmp on 1/3/2021.
//

#ifndef PAC_MAN_LTEXTURE_H
#define PAC_MAN_LTEXTURE_H

#include "../common/pac_common.h"

//Our texture structure
typedef struct {
    SDL_Texture *mTexture;
    int mWidth;
    int mHeight;
} LTexture;

//Extern free function to clear loaded surface
extern void LTexture_free(LTexture *obj);

//Extern load from file function to load surface from file
extern bool LTexture_loadFromFile(LTexture *obj, char *path);

//Extern render function to render surface to window
extern void
LTexture_render(LTexture *obj, int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip);

#endif //PAC_MAN_LTEXTURE_H