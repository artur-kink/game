#include "Drawer.hpp"

Drawer* Drawer::drawer = NULL;

Drawer::Drawer(){

}

Drawer* Drawer::instance(){
    if(drawer == NULL){
        drawer = new Drawer();
    }
    return drawer;
}

uint32_t Drawer::init(SDL_Renderer* renderer){
    sdlRenderer = renderer;

    font = TTF_OpenFont("04B03.ttf", 16);
    if(font == NULL){
        std::cout << "TTF_OpenFont: " << SDL_GetError() << std::endl;
        return 1;
    }
    return 0;
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
    destRect.x = 0;
    destRect.y = y;
    destRect.w = textW;
    destRect.h = textH;

    SDL_RenderCopy(sdlRenderer, textTexture, &textRect, &destRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void Drawer::cleanup(){
    if(font){
        TTF_CloseFont(font);
        font = NULL;
    }
}
