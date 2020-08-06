#ifndef PONG_HPP
# define PONG_HPP

#include <iostream>
#include <strstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <chrono>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
using namespace std;

const int WINDOW_WIDTH  = 250;
const int WINDOW_HEIGHT = 250;
const int RACKET_WIDTH  = 50;
const int RACKET_HEIGHT = 100;

enum Key {
    Key1Up = 0,
    Key1Down,
    Key2Up,
    Key2Down,
    KeyPous,
    KeyEsc
};

struct PongInit {

    SDL_Window      *window = nullptr ;
    SDL_Renderer    *renderer = nullptr ;
    bool            ifExit = false ;


    vector<string>  PathBalls = {"../resources/images/Balls/Ball1.png",
                                 "../resources/images/Balls/Ball2.png",
                                 "../resources/images/Balls/Ball3.png",
                                 "../resources/images/Balls/Ball4.png",
                                 "../resources/images/Balls/Ball5.png",
                                 "../resources/images/Balls/Ball6.png",
                                 "../resources/images/Balls/Ball7.png",
                                 "../resources/images/Balls/Ball8.png",
                                 "../resources/images/Balls/Ball9.png",
                                 "../resources/images/Balls/Ball10.png",
                                 "../resources/images/Balls/Ball11.png",
                                 "../resources/images/Balls/Ball12.png",
                                 "../resources/images/Balls/Ball13.png",
                                 "../resources/images/Balls/Ball14.png",
                                 "../resources/images/Balls/Ball15.png"};
    vector<string>  PathBackgrounds = {"../resources/images/Backgrounds/Background1.png",
                                      "../resources/images/Backgrounds/Background2.png",
                                      "../resources/images/Backgrounds/Background3.png"};
    vector<string>  PathLeftRacket = {"../resources/images/Rackets/Krampus1.png",
                                      "../resources/images/Rackets/Racket1.png"};
    vector<string>  PathRightRacket = {"../resources/images/Rackets/Krampus2.png",
                                       "../resources/images/Rackets/Racket2.png"};


    int             NumPathBalls = 11;
    int             NumPathBackground = 1;
    int             NumPathLeftRacket = 2;
    int             NumPathRightRacket = 1;


    int             ScoreMax = 10;
    int             RacketSpeed = 3;
    int             MaxBallSpeed_x = 5;
    int             MaxBallSpeed_y = 2;
};

class Vect {
public:
    Vect() : x(0), y(0) {}
    Vect(int x, int y) : x(x), y(y) {}

    Vect operator+(Vect const& rhs) {
        return Vect(x + rhs.x, y + rhs.y);
    }
    Vect& operator+=(Vect const& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    Vect operator*(int rhs) {
        return Vect(x * rhs, y * rhs);
    }
    int x, y;
};

class RectPong {
public:
    RectPong() {
        setColorSetNow(this->color_set1);
        cout << "RectPong created...." << endl; };
    ~RectPong() { cout << "RectPong destroyed...." << endl; };

    void        InitRectPong(int y, int x, int h, int w) {
        _rectPong.y = y;
        _rectPong.x = x;
        _rectPong.h = h;
        _rectPong.w = w;
    }

    void        setPositionRect(int y, int x) {
        _rectPong.y = y;
        _rectPong.x = x;
    }

    SDL_Rect&   getRectPong() { return this->_rectPong; };

//    void        RenderDrawRectPongSet2(SDL_Renderer *renderer) {
//        SDL_SetRenderDrawColor(renderer, color_set2.r, color_set2.g, color_set2.b, color_set2.a);
//        SDL_RenderDrawRect(renderer, &_rectPong);
//    }


    void        RenderFillRectPongSet(SDL_Renderer *renderer) {
        SDL_SetRenderDrawColor(renderer, color_setNow.r, color_setNow.g, color_setNow.b, color_setNow.a);
        SDL_RenderFillRect(renderer, &_rectPong);
    }

    SDL_Color       getColorSet1() { return this->color_set1; };

    SDL_Color       getColorSet2() { return this->color_set2; };

    SDL_Color       getColorSet3() { return this->color_set3; };

    void        setColorSetNow(SDL_Color col) { this->color_setNow = col; };

private:
    SDL_Rect        _rectPong;
    SDL_Color       color_set1 = {200, 100, 0, 255};
    SDL_Color       color_set2 = {255, 255, 60, 255};
    SDL_Color       color_set3 = {240, 60, 60, 255};
    SDL_Color       color_setNow;
};


#endif
