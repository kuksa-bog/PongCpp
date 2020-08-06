#include "View.hpp"

bool    View::Running() {
    Init();
    while (ifContinue()) {
        Events();
        if (!ifContinue() && getIfExit()) {
            Clean();
            return false ;
        } if (!ifContinue() && !getIfExit()) {
            Clean();
            return true ;
        } else {
            Update();
            Renderer();
        }
    }
    Clean();
    return true ;
}


bool    View::LoadAllText(int size) {
    int i = 1;
    for (const string &s : getStringText()) {
        if (!getObjectText()[i++].loadObjectTextPlay(getRenderer(), s, size))
            return false ;
    }
    return true;
}

void    View::InitText(int ind) {}

void          View::DrawAllText() {
    for (auto& m : getObjectText()) {
        m.second.Draw(getRenderer());
    }
}

void    View::setPongInit(struct PongInit& pongInit) {
    setRenderer(pongInit.renderer);
    setIfExit(pongInit.ifExit);
    this->PongInit.NumPathBalls = pongInit.NumPathBalls;
    this->PongInit.NumPathBalls = pongInit.NumPathBalls;
    this->PongInit.NumPathBackground = pongInit.NumPathBackground;
    this->PongInit.NumPathLeftRacket = pongInit.NumPathLeftRacket;
    this->PongInit.NumPathRightRacket = pongInit.NumPathRightRacket;
    this->PongInit.ScoreMax = pongInit.ScoreMax;
    this->PongInit.RacketSpeed = pongInit.RacketSpeed;
    this->PongInit.MaxBallSpeed_x = pongInit.MaxBallSpeed_x;
    this->PongInit.MaxBallSpeed_y = pongInit.MaxBallSpeed_y;
};

void    View::updatePongInit(struct PongInit& pongInit) {
    pongInit.renderer = this->PongInit.renderer;
    pongInit.ifExit = getIfExit();
    pongInit.NumPathBalls = this->PongInit.NumPathBalls;
    pongInit.NumPathBalls = this->PongInit.NumPathBalls;
    pongInit.NumPathBackground = this->PongInit.NumPathBackground;
    pongInit.NumPathLeftRacket = this->PongInit.NumPathLeftRacket;
    pongInit.NumPathRightRacket = this->PongInit.NumPathRightRacket;
    pongInit.ScoreMax = this->PongInit.ScoreMax;
    pongInit.RacketSpeed = this->PongInit.RacketSpeed;
    pongInit.MaxBallSpeed_x = this->PongInit.MaxBallSpeed_x;
    pongInit.MaxBallSpeed_y = this->PongInit.MaxBallSpeed_y;
}
