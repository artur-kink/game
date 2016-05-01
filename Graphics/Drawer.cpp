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

    LOG(INFO) << "Create draw texture\n";
    drawTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 562, 384);
    if(drawTexture == NULL){
        return 1;
    }

    LOG(INFO) << "Surface created\n";

    LOG(INFO) << "Loading Textures\n";
    tilesTexture = loadTexture("tiles.png");
    if (tilesTexture == NULL){
        return 1;
    }

    spritesTexture = loadTexture("sprites.png");
    if (spritesTexture == NULL){
        return 1;
    }
    LOG(INFO) << "Textures Loaded\n";

    font = TTF_OpenFont("04B03.ttf", 12);
    if(font == NULL){
        LOG(ERROR) << "TTF_OpenFont: " << SDL_GetError() << "\n";
        return 2;
    }

    loadSprites();
    return 0;
}

void Drawer::setOffset(int32_t x, int32_t y){
    offsetX = x;
    offsetY = y;
}

void Drawer::startDraw(){
    //SDL_RenderClear(sdlRenderer);
    SDL_SetRenderTarget(sdlRenderer, drawTexture);
}

void Drawer::finishDraw(){
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = 512;
    src.h = 384;

    SDL_Rect dest;
    dest.x = 0;
    dest.y = 0;
    dest.w = 1024;
    dest.h = 768;
    
    SDL_SetRenderTarget(sdlRenderer, NULL);
    SDL_RenderCopy(sdlRenderer, drawTexture, &src, &dest);
    SDL_RenderPresent(sdlRenderer);
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
    dest.x = x+offsetX;
    dest.y = y+offsetY;
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

void Drawer::drawSprite(Sprite* sprite, int32_t x, int32_t y){
    
    SDL_Rect pDest;
    pDest.x = x+offsetX;
    pDest.y = y+offsetY;
    pDest.w = sprite->rect.w;
    pDest.h = sprite->rect.h;
    SDL_RenderCopy(sdlRenderer, spritesTexture, &sprite->rect, &pDest);
}

SDL_Texture* Drawer::loadTexture(const char* fileName){
    SDL_Texture* texture = IMG_LoadTexture(sdlRenderer, fileName);
    if (texture == NULL){
        LOG(ERROR) << "IMG_LoadTexture: " << SDL_GetError() << "\n";
        return NULL;
    }
    return texture;
}

SDL_Texture* Drawer::getSpriteTexture(const char* textureName){
    for(uint32_t i = 0; i < spriteTextureNames.size(); i++){
        if(strcmp(textureName, spriteTextureNames[i]) == 0)
            return spriteTextures[i];
    }
    return NULL;
}

SpriteBase* Drawer::getSprite(const char* name){
    for(uint32_t i = 0; i < sprites.size(); i++){
        if(sprites[i]->name && strcmp(sprites[i]->name, name) == 0)
            return sprites[i];
    }
    return NULL;
}

void Drawer::parseSprite(xmlNodePtr node, SpriteSet* currentSet){
    if(node == NULL)
        return;

    for(xmlNodePtr curNode = node->children; curNode; curNode = curNode->next) {
        if(strcmp((const char*)curNode->name, "set") == 0){
            LOG(INFO) << "Set\n";
            SpriteSet* set = new SpriteSet();

            xmlChar *name = xmlGetProp(curNode, (const xmlChar*)"name");
            if(name != NULL){
                set->name = (char*)malloc(strlen((char*)name)+1);
                strcpy(set->name, (char*)name);
            }
    
            if(currentSet != NULL)
                currentSet->sprites.push_back(set);
            else
                sprites.push_back(set);

            parseSprite(curNode, set);
        }else if(strcmp((const char*)curNode->name, "sprite") == 0){
            Sprite* sprite = new Sprite();
            if(currentSet != NULL)
                currentSet->sprites.push_back(sprite);
            else
                sprites.push_back(sprite);
            LOG(INFO) << "Sprite\n";

            xmlChar *name = xmlGetProp(curNode, (const xmlChar*)"name");
            if(name != NULL){
                sprite->name = (char*)malloc(strlen((char*)name)+1);
                strcpy(sprite->name, (char*)name);
            }

            xmlChar* fileName = xmlGetProp(curNode, (const xmlChar*)"file");
            LOG(INFO) << "FileName: " << fileName << "\n";
            SDL_Texture* texture = getSpriteTexture((const char*)fileName);
            if(texture == NULL){
                texture = loadTexture((const char*)fileName);
                if(texture == NULL){
                    LOG(ERROR) << "Failed to load sprite texture " << fileName << "\n";
                }
                spriteTextures.push_back(texture);
                char *textureName = (char*)malloc(strlen((char*)fileName)+1);
                strcpy(textureName, (char*)fileName);
                spriteTextureNames.push_back(textureName);
                sprite->texture = texture;
            }

            xmlChar* xPos = xmlGetProp(curNode, (const xmlChar*)"x");
            xmlChar* yPos = xmlGetProp(curNode, (const xmlChar*)"y");
            xmlChar* width = xmlGetProp(curNode, (const xmlChar*)"w");
            xmlChar* height = xmlGetProp(curNode, (const xmlChar*)"h");
            if(xPos == NULL || yPos == NULL || width == NULL || height == NULL)
                LOG(ERROR) << "Expected sprite property missing\n";

            sprite->rect.x = atoi((const char*)xPos);
            sprite->rect.y = atoi((const char*)yPos);
            sprite->rect.w = atoi((const char*)width);
            sprite->rect.h = atoi((const char*)height);
            LOG(INFO) << "Rect: " << sprite->rect.x << "," << sprite->rect.y << " " << sprite->rect.w << "x" << sprite->rect.h << "\n";
        }
    }
}

void Drawer::loadSprites(){
    // Init libxml2
    LIBXML_TEST_VERSION
    
    xmlDocPtr doc = xmlReadFile("sprites.xml", NULL, 0);

    if(doc == NULL){
        LOG(ERROR) << "Failed to parse sprites.xml\n";
    }

    xmlNodePtr rootNode = xmlDocGetRootElement(doc);
    LOG(INFO) << "Root Node: " << rootNode->name << "\n";
    parseSprite(rootNode, NULL);

    xmlFreeDoc(doc);
    // Xml cleanup
    xmlCleanupParser();
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
