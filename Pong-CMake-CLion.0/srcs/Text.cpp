#include "Object.hpp"

bool    Text::LoadText(SDL_Renderer* renderer, const string &message, SDL_Color color_txt, int size)
{
    TTF_Font *font = TTF_OpenFont("../resources/font/DejaVuSansMono.ttf", size);
    if (font == nullptr){
        cout << "TTF_OpenFont! SDL_ttf Error: " << TTF_GetError() << endl;
        return false;
    }
    SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color_txt);
    if (surf == nullptr){
        TTF_CloseFont(font);
        cout << "TTF_RenderText_Blended! SDL Error: " << SDL_GetError() << endl;
        return false;
    }
    setObject(SDL_CreateTextureFromSurface(renderer, surf));
    if (getObject() == nullptr){
        cout << "SDL_CreateTextureFromSurface! SDL Error: " << SDL_GetError() << endl;
        return false ;
    }
    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
    return true ;
}

void            Text::Update(SDL_Renderer *renderer, const string &message, int size) {
    CleanObject();
    updateColorNow();
    LoadText(renderer, message, getColorNow(), size);
}

void            Text::UpdateSet(SDL_Renderer *renderer, const string &message, int size, int Tipe) {
    CleanObject();
    if (Tipe == 1)
        updateColorSet1();
    else if (Tipe == 2)
        updateColorSet2();
    else if (Tipe == 3)
        updateColorSet3();
    LoadText(renderer, message, getColorSet(), size);
}

bool    Text::loadObjectText(SDL_Renderer *renderer, const string &message, int size) {
    return LoadText(renderer, message, getColorNow(), size);
}

bool    Text::loadObjectTextPlay(SDL_Renderer *renderer, const string &message, int size) {
    return LoadText(renderer, message, this->color_play, size);
}

bool    Text::loadObjectTextSet1(SDL_Renderer *renderer, const string &message, int size) {
    return LoadText(renderer, message, this->color_set1, size);
}

bool    Text::loadObjectTextSet3(SDL_Renderer *renderer, const string &message, int size) {
    return LoadText(renderer, message, this->color_set3, size);
}
