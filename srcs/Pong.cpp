#include "../include/Pong.hpp"

bool init(wind &w)
{
    bool success = true;
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        success = false;
    } else if ( TTF_Init() == -1 ) {
        cout << "SDL_ttf could not initialize! SDL Error: " << TTF_GetError() << endl;
        success = false;
    } else {
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
        w.wallHitSound = Mix_LoadWAV("WallHit.wav");
        w.racketHitSound = Mix_LoadWAV("PaddleHit.wav");
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
            cout << "Warning: Linear texture filtering not enabled!" << endl;
        }
        w.window = SDL_CreateWindow( "Pong-bkuksa", SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
        if( w.window == nullptr ) {
            cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
            success = false;
        } else {
            w.renderer = SDL_CreateRenderer( w.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if ( w.renderer == nullptr ) {
                cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
                success = false;
            } else {
                SDL_SetRenderDrawColor( w.renderer, 0x0, 0x0, 0x0, 0xFF );
            }
        }
    }

    return success;
}

void close(wind &w)
{
    SDL_DestroyTexture(w.image_bll);
    SDL_DestroyTexture(w.image_racket1);
    SDL_DestroyTexture(w.image_racket2);
    SDL_DestroyTexture(w.Background);
    SDL_DestroyRenderer(w.renderer);
    SDL_DestroyWindow(w.window);
    Mix_FreeChunk(w.wallHitSound);
    Mix_FreeChunk(w.racketHitSound);
    w.renderer = nullptr;
    w.window = nullptr;

    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend){
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    SDL_QueryTexture(tex, nullptr, nullptr, &pos.w, &pos.h);
    SDL_RenderCopy(rend, tex, nullptr, &pos);
}

bool loadMedia(wind &w)
{
    SDL_Surface *loadedImage = SDL_LoadBMP("Bub.bmp");
    SDL_Surface *loadedImage2 = SDL_LoadBMP("Yet.bmp");
    SDL_Surface *loadedImage3 = SDL_LoadBMP("Krampus.bmp");
    SDL_Surface *loadedImage4 = SDL_LoadBMP("map.bmp");
    if (loadedImage != nullptr && loadedImage2 != nullptr && loadedImage3 != nullptr && loadedImage4 != nullptr){
        w.image_bll = SDL_CreateTextureFromSurface(w.renderer, loadedImage);
        SDL_FreeSurface(loadedImage);
        w.image_racket1 = SDL_CreateTextureFromSurface(w.renderer, loadedImage2);
        SDL_FreeSurface(loadedImage2);
        w.image_racket2 = SDL_CreateTextureFromSurface(w.renderer, loadedImage3);
        SDL_FreeSurface(loadedImage3);
        w.Background = SDL_CreateTextureFromSurface(w.renderer, loadedImage4);
        SDL_FreeSurface(loadedImage4);
    }
    else {
        std::cout << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void    DrawsTheNet(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (int y = 0; y < WINDOW_HEIGHT; ++y) {
        if (y % 5) {
            SDL_RenderDrawPoint(renderer, WINDOW_WIDTH / 2, y);
        }
    }
}

void PutText(wind &w, int y_txt, SDL_Texture *texture, int i) {
    int iW, iH, x = 0, y = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &iW, &iH);
    if (i == 1) {
        x = WINDOW_WIDTH / 2 - iW / 2;
        y = y_txt - iH / 2;
    } else if (i == 2) {
        x = 20 - iW / 2;
        y = y_txt - iH / 2;
    }
    ApplySurface(x, y, texture, w.renderer);
}

SDL_Texture* RenderText(const string &message, const string &fontFile, wind &w, int i)
{
    if (i == 1)
        w.font = TTF_OpenFont(fontFile.c_str(), w.fontSize);
    else
        w.font = TTF_OpenFont(fontFile.c_str(), 20);
    if (w.font == nullptr){
        cout << "TTF_OpenFont! SDL_ttf Error: " << TTF_GetError() << endl;
        return nullptr;
    }
    SDL_Surface *surf = TTF_RenderText_Blended(w.font, message.c_str(), w.color_txt);
    if (surf == nullptr){
        TTF_CloseFont(w.font);
        cout << "TTF_RenderText_Blended! SDL Error: " << SDL_GetError() << endl;
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(w.renderer, surf);
    if (texture == nullptr){
        cout << "SDL_CreateTextureFromSurface! SDL Error: " << SDL_GetError() << endl;
    }

    SDL_FreeSurface(surf);
    TTF_CloseFont(w.font);

    return texture;
}

bool IfTouchRacket(Ball &ball, const Racket &racket, const wind &w) {
    if (ball.position.x - w.ball_width / 2 >= racket.position.x + 10) {
        return false;
    }
    if (ball.position.x + w.ball_width / 2 <= racket.position.x - 10) {
        return false;
    }
    if (ball.position.y - w.ball_height / 2 >= racket.position.y + w.racket_height / 2) {
        return false;
    }
    if (ball.position.y + w.ball_height / 2 <= racket.position.y - w.racket_height / 2) {
        return false;
    }
    if (ball.speed.x < 0) {
        ball.position.x += ((racket.position.x + w.racket_width / 2) - (ball.position.x - w.ball_width / 2));
    } else if (ball.speed.x > 0) {
        ball.position.x += ((racket.position.x - w.racket_width / 2) - (ball.position.x + w.ball_width / 2));
    }
    return true;
}

void    WidthAndHeightOfObjects(wind &w) {
    int iW, iH;
    SDL_QueryTexture(w.image_bll, nullptr, nullptr, &iW, &iH);
    w.ball_width = iW;
    w.ball_height = iH;
    w.racket_width = 60;
    w.racket_height = 100;
}

void    RenderBackground(wind &w) {
    SDL_Rect destRect;
    destRect.h = 720;
    destRect.w = 1280;
    destRect.x = 0;
    destRect.y = 0;

    SDL_RenderCopy(w.renderer, w.Background, nullptr, &destRect);
}

void    Winner(wind &w, Ball &ball, Racket &RacketOne, Racket &RacketTwo) {
//    Yeti
//    Krampus
    bool running = true;
    SDL_Event event;
    string path = "DejaVuSansMono.ttf";
    SDL_Color color_txt2 = w.color_txt;
    w.color_txt = {255, 100, 100, 255};
    SDL_Texture *First_Win = RenderText("** YETI WINNER !!!! **", path, w, 1);
    SDL_Texture *Second_Win = RenderText("** KRAMPUS WINNER !!!! **", path, w, 1);
    w.color_txt = color_txt2;
    SDL_Texture *Exit = RenderText("Exit", path, w, 1);

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT : {
                    running = false;
                    break;
                }
                case SDL_KEYDOWN : {
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE : {
                            running = false;
                            break;
                        }
                    }
                    break;
                }
                case SDL_MOUSEBUTTONDOWN : {
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int x = event.button.x, y = event.button.y;
                        if (x >= (WINDOW_WIDTH / 2) - 40 && x <= (WINDOW_WIDTH / 2) + 40
                            && y >= static_cast<int>(WINDOW_HEIGHT / 2.4f) - 15
                            && y <= static_cast<int>(WINDOW_HEIGHT / 2.4f) + 22) {
                            SDL_DestroyTexture(First_Win);
                            SDL_DestroyTexture(Second_Win);
                            SDL_DestroyTexture(Exit);
                            return;
                        }
                    }
                    break;
                }
                case SDL_MOUSEMOTION : {
                    int xMouse, yMouse;
                    SDL_GetMouseState(&xMouse, &yMouse);
                    if (xMouse >= (WINDOW_WIDTH / 2) - 40 && xMouse <= (WINDOW_WIDTH / 2) + 40
                        && yMouse >= static_cast<int>(WINDOW_HEIGHT / 2.4f) - 15 &&
                        yMouse <= static_cast<int>(WINDOW_HEIGHT / 2.4f) + 22) {
                        w.color_txt = {255, 255, 100, 255};
                        SDL_RenderClear(w.renderer);
                        Exit = RenderText("Exit", path, w, 1);
                    } else {
                        w.color_txt = {255, 255, 255, 255};
                        Exit = RenderText("Exit", path, w, 1);
                    }
                    break;
                }
            }
        }
        SDL_RenderClear(w.renderer);
        RenderBackground(w);
        SDL_Color color_txt = w.color_txt;
        w.color_txt = {255, 100, 100, 255};
        SDL_Texture *ScoreOneText = RenderText(to_string(ball.ScoreOne) + "/8", path, w, 1);
        SDL_Texture *ScoreTwoText = RenderText(to_string(ball.ScoreTwo) + "/8", path, w, 1);
        ball.PutText(w.renderer, 30, ScoreOneText, 1);
        ball.PutText(w.renderer, 30, ScoreTwoText, 0);
        w.color_txt = color_txt;
        if (w.Win == 1)
            PutText(w, WINDOW_HEIGHT / (4), First_Win, 1);
        else
            PutText(w, WINDOW_HEIGHT / (4), Second_Win, 1);
        RacketOne.Draw(w.renderer, w.image_racket1);
        RacketTwo.Draw(w.renderer, w.image_racket2);
        PutText(w, static_cast<int>(WINDOW_HEIGHT / 2.4f), Exit, 1);
        SDL_RenderPresent(w.renderer);
    }
    SDL_DestroyTexture(First_Win);
    SDL_DestroyTexture(Second_Win);
    SDL_DestroyTexture(Exit);
}
