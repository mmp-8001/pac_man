//
// Created by mmp on 1/3/2021.
//

#ifndef PAC_MAN_TEXTURE_H
#define PAC_MAN_TEXTURE_H

#include "../common/pac_common.h"

//Our texture structure
typedef struct {
    SDL_Texture *mTexture;
    int mWidth;
    int mHeight;
} LTexture;

//Extern free function to clear loaded surface
extern void TEXTURE_free(LTexture *obj);

//Extern load from file function to load surface from file
extern bool TEXTURE_loadFromFile(LTexture *obj, char *path);

//Extern render function to render surface to window
extern void
TEXTURE_render(LTexture *obj, int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip);

//Extern set alpha function to set alpha channel
extern void TEXTURE_set_alpha(LTexture *obj, int alpha);

//Extern this function to build texture from text
extern bool TEXTURE_FromRenderedText(LTexture *obj, char *textureText, SDL_Color textColor);

#endif //PAC_MAN_TEXTURE_H