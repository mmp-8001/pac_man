//
// Created by mmp on 1/3/2021.
//

#include "LTexture.h"

//This function clear memory and deallocate
extern void LTexture_free(LTexture *obj) {
    //Free texture if it exists
    if (obj->mTexture != NULL) {
        SDL_DestroyTexture(obj->mTexture);
        obj->mTexture = NULL;
        obj->mWidth = 0;
        obj->mHeight = 0;
    }
}

//This function load surface from specified file
extern bool LTexture_loadFromFile(LTexture *obj, char *path) {
    //Free up if we have data in that chunk of memory
    LTexture_free(obj);

    //The final texture
    SDL_Texture *newTexture = NULL;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    } else {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        } else {
            //Get image dimensions
            obj->mWidth = loadedSurface->w;
            obj->mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    //Return success
    obj->mTexture = newTexture;
    return obj->mTexture != NULL;
}

//This function render our loaded surface to window
extern void
LTexture_render(LTexture *obj, int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip) {
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, obj->mWidth, obj->mHeight};

    //Set clip rendering dimensions
    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(gRenderer, obj->mTexture, clip, &renderQuad, angle, center, flip);
}