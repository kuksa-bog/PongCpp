#ifndef PLAY_HPP
# define PLAY_HPP

#include "Pong.hpp"

class Bot : public Racket {
public:
    Bot(Vect v1, Vect v2, bool move, int flag) : Racket(v1, v2),
    Flag(flag), x1(0), y1(0), x2(0), y2(0) {};
//    void IfBotMove();
    void SearchPlaceHard(Ball &ball, wind &w, float dt);
//    void SearchPlaceEasy();
    void MoveToPlace(float dt);
//    void IncreaseA_Speed_theBall(wind &w, Ball &ball, float dt);
//    void Slow_Down_theBall();
    int Without_Change(float dt);
//    void Wear_theBall();
//    void IfMoveToBall();
    void Update(float dt, int y) override ;

    int      Flag;
//    bool     Move;
    float    x1, y1, x2, y2;
};

#endif
