#include "Object.hpp"

bool Object::loadObject(SDL_Renderer *renderer, const string &path) {
    SDL_Surface *TmpSurf = IMG_Load(path.c_str());
    if ( TmpSurf != nullptr ) {
        this->object = SDL_CreateTextureFromSurface(renderer, TmpSurf);
    } else {
        std::cout << SDL_GetError() << std::endl;
        return false;
    }
    SDL_FreeSurface(TmpSurf);
    return true;
}

void            Object::Draw(SDL_Renderer *renderer) {
    SDL_Rect pos;
    pos.x = getPosition().x;
    pos.y = getPosition().y;
    pos.w = getWidth();
    pos.h = getHeight();
    SDL_RenderCopy(renderer, this->getObject(), nullptr, &pos);
}

bool            Object::ifPositionObject(int x, int y) {
     if (x >= getPosition().x && x <= (getPosition().x + getWidth())) {
        if (y >= getPosition().y && y <= (getPosition().y + getHeight()))
            return true;
    }
    return false;
}
