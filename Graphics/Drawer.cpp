#include "Drawer.hpp"

Drawer* Drawer::drawer = NULL;

Drawer::Drawer(){

}

Drawer* Drawer::instance(){
    if(drawer == NULL)
        drawer = new Drawer();
    return drawer;
}

uint32_t Drawer::init(SDL_Renderer* renderer){
    sdlRenderer = renderer;

    LOG(INFO) << "Loading Textures\n";
    tilesTexture = IMG_LoadTexture(sdlRenderer, "tiles.png");
    if (tilesTexture == NULL){
        LOG(ERROR) << "IMG_LoadTexture: " << SDL_GetError() << "\n";
        return 1;
    }

    spritesTexture = IMG_LoadTexture(sdlRenderer, "sprites.png");
    if (spritesTexture == NULL){
        LOG(ERROR) << "IMG_LoadTexture: " << SDL_GetError() << "\n";
        return 1;
    }
    LOG(INFO) << "Textures Loaded\n";

    font = TTF_OpenFont("04B03.ttf", 12);
    if(font == NULL){
        std::cout << "TTF_OpenFont: " << SDL_GetError() << std::endl;
        return 2;
    }
    return 0;
}

void Drawer::setOffset(int32_t x, int32_t y){
    offsetX = x;
    offsetY = y;
}

void Drawer::drawText(const char* text, int32_t x, int32_t y){
    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(sdlRenderer, textSurface);

    int textW, textH;
    SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
    SDL_Rect textRect;
    textRect.x = 0;
    textRect.y = 0;
    textRect.w = textW;
    textRect.h = textH;

    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = textW;
    destRect.h = textH;

    SDL_RenderCopy(sdlRenderer, textTexture, &textRect, &destRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void Drawer::drawTile(uint32_t tile, int32_t x, int32_t y){
    SDL_Rect src;
    src.x = (tile%30)*TILE_WIDTH;
    src.y = (tile/30)*TILE_HEIGHT;
    src.w = TILE_WIDTH;
    src.h = TILE_HEIGHT;

    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = TILE_WIDTH;
    dest.h = TILE_HEIGHT;
    SDL_RenderCopy(sdlRenderer, tilesTexture, &src, &dest);
}

void Drawer::drawSprite(uint32_t sprite, int32_t x, int32_t y){
    SDL_Rect pSrc;
    pSrc.x = (sprite%10)*40;
    pSrc.y = (sprite/10)*40;
    pSrc.w = 40;
    pSrc.h = 40;

    SDL_Rect pDest;
    pDest.x = x+offsetX;
    pDest.y = y+offsetY;
    pDest.w = 40;
    pDest.h = 40;
    SDL_RenderCopy(sdlRenderer, spritesTexture, &pSrc, &pDest);
}

void Drawer::cleanup(){
    if(tilesTexture){
        SDL_DestroyTexture(tilesTexture);
    }

    if(spritesTexture){
        SDL_DestroyTexture(spritesTexture);
    }

    if(font){
        TTF_CloseFont(font);
        font = NULL;
    }
}
