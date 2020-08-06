#include "Object.hpp"

bool        Ball::Update(int dt, Vect& posr1, Vect& posr2, Vect& spdr1, Vect& spdr2, PongInit& pongInit) {
    bool i = UpdateSpeed(posr1, posr2, spdr1, spdr2, pongInit);
    setPosition((getPosition() += getSpeed() * dt));
    return i;
}

bool        Ball::UpdateSpeed(Vect& posr1, Vect& posr2, Vect& spdr1, Vect& spdr2, PongInit& pongInit) {
    bool i = false ;
    if (ifTouchWall())
        i = true;
    if (ifTouchRacket(posr1, posr2, spdr1, spdr2, pongInit))
        i = true ;
    return i;
}

bool        Ball::ifTouchWall() {
    bool b = false;
    if (getPosition().x <= 0) {
        getPosition().x = WINDOW_WIDTH * 5 / 2 - getWidth() / 2;
        getSpeed().x = -getSpeed().x;
        setScoreSecond(getScoreSecond() + 1);
        b =  true ;
    } else if (getPosition().x + getWidth() >= WINDOW_WIDTH * 5) {
        getPosition().x = WINDOW_WIDTH * 5 / 2 - getWidth() / 2;
        getSpeed().x = -getSpeed().x;
        setScoreFirst(getScoreFirst() + 1);
    }

    if (getPosition().y <= 0) {
        Mix_PlayChannel(-1, wallHitSound, 0);
        getPosition().y = 0;
        getSpeed().y = -getSpeed().y;
    } else if (getPosition().y + getHeight() >= WINDOW_HEIGHT * 3) {
        Mix_PlayChannel(-1, wallHitSound, 0);
        getPosition().y = WINDOW_HEIGHT * 3 - getHeight();
        getSpeed().y = -getSpeed().y;
    }
    return b ;
}

bool        Ball::ifTouchRacket(Vect &posr1, Vect &posr2, Vect& spdr1, Vect& spdr2, PongInit& pongInit) {
    int     i = 0;
    if (getPosition().x <= posr1.x + RACKET_WIDTH - getWidth() / 2 // (
        && ((getPosition().y <= posr1.y + RACKET_HEIGHT)
        && (getPosition().y >= posr1.y - getHeight()))) {          // )
        i = 1;
        getSpeed().x = -getSpeed().x;
        getPosition().x = posr1.x + RACKET_WIDTH;
        Mix_PlayChannel(-1, racketHitSound, 0);
    } else if ((getPosition().x >= posr2.x - getWidth() / 2)           // (
        && ((getPosition().y <= posr2.y + RACKET_HEIGHT)
            && (getPosition().y >= posr2.y - getHeight()))) {
        i = 2;
        getSpeed().x = -getSpeed().x;
        getPosition().x = posr2.x - getWidth();
        Mix_PlayChannel(-1, racketHitSound, 0);
    }

    if ( i ) {
//        if (getSpeed().y >= 0)
//            getSpeed().y += 3;
//        else if (getSpeed().y < 0)
//            getSpeed().y -= 3;

        if (i == 1) {

              if (spdr1.y)
                  getSpeed().y = (getSpeed().y + 1 >= pongInit.MaxBallSpeed_y) ? pongInit.MaxBallSpeed_y : getSpeed().y + 1;
              else if (spdr1.y < 0)
                  getSpeed().y = (getSpeed().y - 1 <= -pongInit.MaxBallSpeed_y) ? -pongInit.MaxBallSpeed_y : getSpeed().y - 1;

            if (getPosition().y + getHeight() >= posr1.y &&
                getPosition().y + getHeight() <= posr1.y + RACKET_HEIGHT / 5 + getHeight() / 2)
                getSpeed().y = (getSpeed().y - 2 <= -pongInit.MaxBallSpeed_y) ? -pongInit.MaxBallSpeed_y : getSpeed().y - 2;
            else if (getPosition().y + getHeight() > posr1.y + RACKET_HEIGHT / 5 + getHeight() / 2 &&
                     getPosition().y + getHeight() <= posr1.y + RACKET_HEIGHT / 5 * 2 + getHeight() / 2)
                getSpeed().y = (getSpeed().y - 1 <= -pongInit.MaxBallSpeed_y) ? -pongInit.MaxBallSpeed_y : getSpeed().y - 1;
            else if (getPosition().y + getHeight() > posr1.y + RACKET_HEIGHT / 5 * 3 + getHeight() / 2 &&
                     getPosition().y + getHeight() <= posr1.y + RACKET_HEIGHT / 5 * 4 + getHeight() / 2)
                getSpeed().y = (getSpeed().y + 1 >= pongInit.MaxBallSpeed_y) ? pongInit.MaxBallSpeed_y : getSpeed().y + 1;
            else if (getPosition().y + getHeight() > posr1.y + RACKET_HEIGHT / 5 * 4 + getHeight() / 2 &&
                     getPosition().y + getHeight() <= posr1.y + RACKET_HEIGHT + getHeight())
                getSpeed().y = (getSpeed().y + 2 >= pongInit.MaxBallSpeed_y) ? pongInit.MaxBallSpeed_y : getSpeed().y + 2;
        } else {

              if (spdr2.y)
                  getSpeed().y = (getSpeed().y + 1 >= pongInit.MaxBallSpeed_y) ? pongInit.MaxBallSpeed_y : getSpeed().y + 1;
              else if (spdr2.y < 0)
                  getSpeed().y = (getSpeed().y - 1 <= -pongInit.MaxBallSpeed_y) ? -pongInit.MaxBallSpeed_y : getSpeed().y - 1;

            if (getPosition().y + getHeight() >= posr2.y &&
                getPosition().y + getHeight() <= posr2.y + RACKET_HEIGHT / 5 + getHeight() / 2)
                getSpeed().y = (getSpeed().y - 2 <= -pongInit.MaxBallSpeed_y) ? -pongInit.MaxBallSpeed_y : getSpeed().y - 2;
            else if (getPosition().y + getHeight() > posr2.y + RACKET_HEIGHT / 5 + getHeight() / 2 &&
                     getPosition().y + getHeight() <= posr2.y + RACKET_HEIGHT / 5 * 2 + getHeight() / 2)
                getSpeed().y = (getSpeed().y - 1 <= -pongInit.MaxBallSpeed_y) ? -pongInit.MaxBallSpeed_y : getSpeed().y - 1;
            else if (getPosition().y + getHeight() > posr2.y + RACKET_HEIGHT / 5 * 3 + getHeight() / 2 &&
                     getPosition().y + getHeight() <= posr2.y + RACKET_HEIGHT / 5 * 4 + getHeight() / 2)
                getSpeed().y = (getSpeed().y + 1 >= pongInit.MaxBallSpeed_y) ? pongInit.MaxBallSpeed_y : getSpeed().y + 1;
            else if (getPosition().y + getHeight() > posr2.y + RACKET_HEIGHT / 5 * 4 + getHeight() / 2 &&
                     getPosition().y + getHeight() <= posr2.y + RACKET_HEIGHT + getHeight())
                getSpeed().y = (getSpeed().y + 2 >= pongInit.MaxBallSpeed_y) ? pongInit.MaxBallSpeed_y : getSpeed().y + 2;
        }
    }
    return i == 1;

}
