#ifndef PONG_HPP
# define PONG_HPP

#include <iostream>
#include <strstream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <chrono>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
using namespace std;

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 650;
const float RACKET_SPEED = 0.5f;
const float BALL_SPEED = 0.6f;

void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend);

enum Key {
    Key1Up = 0,
    Key1Down,
    Key2Up,
    Key2Down
};

class Vect {
public:
    Vect() : x(0.0f), y(0.0f) {}
    Vect(float x, float y) : x(x), y(y) {}

    Vect operator+(Vect const& rhs) {
        return Vect(x + rhs.x, y + rhs.y);
    }
    Vect& operator+=(Vect const& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    Vect operator*(float rhs) {
        return Vect(x * rhs, y * rhs);
    }
    float x, y;
};

class Ball
{
public:
    Ball(Vect position, Vect speed) : position(position), speed(speed) {
        ScoreOne = 0;
        ScoreTwo = 0;
    }
    void Draw(SDL_Renderer* renderer, SDL_Texture *image_bll) {
        int iW, iH;
        SDL_QueryTexture(image_bll, NULL, NULL, &iW, &iH);
        int x = position.x - iW / 2;
        int y = position.y - iH / 2;
        ApplySurface(x, y, image_bll, renderer);
    }
    int IfTouchWall(int h, int w, Mix_Chunk* wallHitSound) {
        if (position.x - w / 2 < 0.0f) {
            position.x = WINDOW_WIDTH / 2.0f;
            speed.x = -speed.x;
            speed.y = 0.0f;
            ScoreTwo++;
            return 1;
        } else if (position.x + w / 2 > WINDOW_WIDTH) {
            position.x = WINDOW_WIDTH / 2.0f;
            speed.x = -speed.x;
            speed.y = 0.0f;
            ScoreOne++;
        } else if (position.y - h / 2 < 0.0f) {
            Mix_PlayChannel(-1, wallHitSound, 0);
            position.y += -(position.y - h / 2);
            speed.y = -speed.y;
        } else if (position.y + h / 2 > WINDOW_HEIGHT) {
            Mix_PlayChannel(-1, wallHitSound, 0);
            position.y += WINDOW_HEIGHT - position.y - h / 2;
            speed.y = -speed.y;
        }
        return 0;
    };
    void PutText(SDL_Renderer *renderer, int y_txt, SDL_Texture *texture, int Num) {
        int iW, iH;
        SDL_QueryTexture(texture, nullptr, nullptr, &iW, &iH);
        int x, y;
        if (Num == 1) {
            x = WINDOW_WIDTH / 4 - iW / 2;
            y = y_txt - iH / 2;
        } else {
            x = 3 * WINDOW_WIDTH / 4 - iW / 2;
            y = y_txt - iH / 2;
        }
        ApplySurface(x, y, texture, renderer);
    }
    void Update(float dt) {
        position += speed * dt;
    }
    int  ScoreOne;
    int  ScoreTwo;
    Vect position;
    Vect speed;
};

class Racket {
public:
    Racket(Vect position, Vect speed) : position(position), speed(speed) {
    }
    void Draw(SDL_Renderer* renderer, SDL_Texture *image_racket) {
        SDL_Rect destRect;
        destRect.h = 100;
        destRect.w = 60;
        destRect.x = position.x - 60 / 2;
        destRect.y = position.y - 100 / 2;

        SDL_RenderCopy(renderer, image_racket, nullptr, &destRect);
    }
    virtual void Update(float dt, int y) {
        position += speed * dt;
        if (position.y - y / 2 < 0) {
            position.y = y / 2;
        } else if (position.y + y / 2 > (WINDOW_HEIGHT)) {
            position.y = WINDOW_HEIGHT - y / 2;
        }
    }
    Vect position;
    Vect speed;
};

struct  wind {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *image_bll = NULL;
    SDL_Texture *image_racket1 = NULL;
    SDL_Texture *image_racket2 = NULL;
    SDL_Texture *Background = NULL;
    int     fontSize = 35;
    SDL_Color color_txt = {255, 255, 255, 255};
    TTF_Font *font;
    int     ball_width;
    int     ball_height;
    int     racket_width;
    int     racket_height;
    Mix_Chunk* wallHitSound = NULL;
    Mix_Chunk* racketHitSound = NULL;
    int     Win;

};

bool IfTouchRacket(Ball &ball, const Racket &paddle, const wind &w);
void DrawsTheNet(SDL_Renderer* renderer);
bool init(wind &w);
void close (wind &w);
bool loadMedia(wind &w);
void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend);
SDL_Texture* RenderText(const string &message, const string &fontFile, wind &w, int i);
void PutText(wind &w, int y_txt, SDL_Texture *texture, int i);
void    WidthAndHeightOfObjects(wind &w);
void    RenderBackground(wind &w);
void    Winner(wind &w, Ball &ball, Racket &RacketOne, Racket &RacketTwo);


#endif
