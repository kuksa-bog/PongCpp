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
    this->_PongInit.NumPathBalls = pongInit.NumPathBalls;
    this->_PongInit.NumPathBalls = pongInit.NumPathBalls;
    this->_PongInit.NumPathBackground = pongInit.NumPathBackground;
    this->_PongInit.NumPathLeftRacket = pongInit.NumPathLeftRacket;
    this->_PongInit.NumPathRightRacket = pongInit.NumPathRightRacket;
    this->_PongInit.ScoreMax = pongInit.ScoreMax;
    this->_PongInit.RacketSpeed = pongInit.RacketSpeed;
    this->_PongInit.MaxBallSpeed_x = pongInit.MaxBallSpeed_x;
    this->_PongInit.MaxBallSpeed_y = pongInit.MaxBallSpeed_y;
}

void    View::updatePongInit(struct PongInit& pongInit) {
    pongInit.renderer = this->_PongInit.renderer;
    pongInit.ifExit = getIfExit();
    pongInit.NumPathBalls = this->_PongInit.NumPathBalls;
    pongInit.NumPathBalls = this->_PongInit.NumPathBalls;
    pongInit.NumPathBackground = this->_PongInit.NumPathBackground;
    pongInit.NumPathLeftRacket = this->_PongInit.NumPathLeftRacket;
    pongInit.NumPathRightRacket = this->_PongInit.NumPathRightRacket;
    pongInit.ScoreMax = this->_PongInit.ScoreMax;
    pongInit.RacketSpeed = this->_PongInit.RacketSpeed;
    pongInit.MaxBallSpeed_x = this->_PongInit.MaxBallSpeed_x;
    pongInit.MaxBallSpeed_y = this->_PongInit.MaxBallSpeed_y;
}
