#ifndef OBJECT_HPP
# define OBJECT_HPP

#include "Pong.hpp"

class Object {
public:
    Object() : _width(0), _height(0) {
        cout << "Object created...." << endl;
        object = nullptr;
    };
    virtual ~Object() {
        if (object)
            CleanObject();
        cout << "Object destroyed...." << endl; };

    void            Init(int h, int w, Vect vect) { setHeight(h); setWidth(w); setPosition(vect); };

    virtual void    Draw(SDL_Renderer* renderer);


    Vect&           getPosition() { return _Position; };

    void            setPosition(Vect& position) { this->_Position = position; }

    int             getHeight() { return this->_height; };

    void            setHeight(int height) { this->_height = height; };

    int             getWidth() { return this->_width; };

    void            setWidth(int width) { this->_width = width; };

    SDL_Texture*    getObject() { return this->object; };

    void            setObject(SDL_Texture* texture) { this->object = texture; };


    virtual bool    loadObject(SDL_Renderer *renderer, const string &path);

    void            CleanObject() { SDL_DestroyTexture(object); object = nullptr; };

    bool            ifPositionObject(int x, int y);

private:
    SDL_Texture*    object;
    int             _width;
    int             _height;
    Vect            _Position;
};





class Texture : public Object {
public:
    Texture() { cout << "Texture created...." << endl; };
    ~Texture() override { cout << "Texture destroyed...." << endl; };
};





class Text : public Object {
public:
    Text() : color_now(1), color_help(true), color_set(1) { cout << "Text created...." << endl; };

    ~Text() override { cout << "Text destroyed...." << endl; };

    bool            loadObjectText(SDL_Renderer *renderer, const string &message, int size);

    bool            loadObjectTextPlay(SDL_Renderer *renderer, const string &message, int size);

    bool            LoadText(SDL_Renderer* renderer, const string &message, SDL_Color color_txt, int size);



    SDL_Color       getColorNow() { return this->color_now == 1 ? this->color_old : this->color_new; };

    void            updateColorNow() { this->color_now = (this->color_now == 1) ? 2 : 1; };

    void            Update(SDL_Renderer *renderer, const string &message, int size);



    void            updateColorHelp() { this->color_help = !this->color_help; };

    void            UpdateHelp(SDL_Renderer *renderer, const string &message, int size);

    SDL_Color       getColorHelp() { return this->color_now ? this->color_help1 : this->color_help2; };



    void            updateColorSet1() { this->color_set = 1; };

    void            updateColorSet2() { this->color_set = 2; };

    void            updateColorSet3() { this->color_set = 3; };

    void            UpdateSet(SDL_Renderer *renderer, const string &message, int size, int Tipe);

    SDL_Color       getColorSet() { if (this->color_set == 1) return  this->color_set1;
                                    else if (this->color_set == 2) return  this->color_set2;
                                    else return  this->color_set3; };

    bool            loadObjectTextSet1(SDL_Renderer *renderer, const string &message, int size);

    bool            loadObjectTextSet3(SDL_Renderer *renderer, const string &message, int size);

private:
    SDL_Color       color_old = {237, 175, 17, 255};
    SDL_Color       color_new = {255, 255, 17, 255};
    SDL_Color       color_play = {60, 60, 60, 255};
    SDL_Color       color_help1 = {240, 60, 60, 255};
    SDL_Color       color_help2 = {60, 60, 240, 255};
    SDL_Color       color_set1 = {200, 100, 0};
    SDL_Color       color_set2 = {255, 255, 60, 255};
    SDL_Color       color_set3 = {240, 60, 60, 255};
    int             color_now;
    bool            color_help;
    int             color_set;
};





class Ball : public Object {
public:
    Ball() : ScoreFirst(0), ScoreSecond(0) { cout << "Ball created...." << endl; };
    ~Ball() override { cout << "Ball destroyed...." << endl; };

    void            Init(int h, int w, Vect vect, Vect speed) {
        this->wallHitSound = Mix_LoadWAV("../resources/sounds/WallHit.wav");
        this->racketHitSound = Mix_LoadWAV("../resources/sounds/PaddleHit.wav");
        setHeight(h); setWidth(w); setPosition(vect); setSpeed(speed); };

    bool            Update(int dt, Vect& posr1, Vect& posr2, Vect& spdr1, Vect& spdr2, PongInit& pongInit);

    bool            UpdateSpeed(Vect& posr1, Vect& posr2, Vect& spdr1, Vect& spdr2, PongInit& pongInit);

    void            setSpeed(Vect& speed) { this->_Speed = speed; }

    Vect&           getSpeed() { return _Speed; };



    int             getScoreFirst() { return this->ScoreFirst; };

    void            setScoreFirst(int score) { this->ScoreFirst = score; };

    string          getStringScoreFirst() { return to_string(getScoreFirst()); };

    int             getScoreSecond() { return this->ScoreSecond; };

    void            setScoreSecond(int score) { this->ScoreSecond = score; };

    string          getStringScoreSecond() { return to_string(getScoreSecond()); };



private:
    bool            ifTouchRacket(Vect& posr1, Vect& posr2, Vect& spdr1, Vect& spdr2, PongInit& pongInit);

    bool            ifTouchWall();

    Vect            _Speed;
    int             ScoreFirst{};
    int             ScoreSecond{};
    Mix_Chunk*      wallHitSound;
    Mix_Chunk*      racketHitSound;
};







class Racket : public Object {
public:
    Racket();
    ~Racket() override { cout << "Racket destroyed...." << endl; };

    void            Init(int h, int w, Vect vect, Vect speed) {
                    setHeight(h); setWidth(w); setPosition(vect); setSpeed(speed); };

    virtual void    Update(int dt);

    void            UpdateSpeed(int s) { this->_Speed.y = s; };

    void            setSpeed(Vect& speed) { this->_Speed = speed; }

    Vect&           getSpeed() { return _Speed; };


private:
    Vect            _Speed;
};







class Bot : public Racket {
public:
    Bot() : _Flag(1), x1(0), y1(0), x2(0), y2(0), _MaxSpeed(0)
    { cout << "Bot created...." << endl; }
    ~Bot() override { cout << "Bot destroyed...." << endl; };

    void            SearchPlaceHard(Ball& ball, int dt);

    void            MoveToPlace(int dt);

    void            Without_Change(int dt);

    void            Update(int dt) override ;

    void            setMaxSpeed(int speed) { this->_MaxSpeed = speed; };

private:
    int             getMaxSpeed() { return this->_MaxSpeed; };

    int             _Flag;
    int             x1, y1, x2, y2;
    int             _MaxSpeed;

};

#endif
