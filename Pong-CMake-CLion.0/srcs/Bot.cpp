#include "Object.hpp"

void        Bot::SearchPlaceHard(Ball& ball, int dt) {
    int     s_x, s_y, p_x, p_y;
    s_x = ball.getSpeed().x;
    s_y = ball.getSpeed().y;
    p_x = ball.getPosition().x;
    p_y = ball.getPosition().y;
    while (p_x <= getPosition().x - ball.getWidth() / 2) {
        if  (p_y <= 0) {
            s_y = -s_y;
            p_y = 0;
        } else if (p_y + ball.getHeight() >= WINDOW_HEIGHT * 3) {
            s_y = -s_y;
            p_y = WINDOW_HEIGHT * 3 - getHeight();
        }
        p_x += s_x * dt;
        p_y += s_y * dt;
    }
    this->x1 = p_x;
    this->y1 = p_y;
}

void        Bot::MoveToPlace(int dt) {
    if (getPosition().y + dt * getMaxSpeed() < this->y2) {
        getSpeed().y = getMaxSpeed();
    } else if (getPosition().y - dt * getMaxSpeed() > this->y2) {
        getSpeed().y = -getMaxSpeed();
    } else {
        getSpeed().y = 0;
    }
}

void         Bot::Without_Change(int dt) {
    this->x2 = this->x1;
    this->y2 = this->y1;
    Bot::MoveToPlace(dt);
}

void        Bot::Update(int dt) {
    if (this->_Flag == 1)
        Without_Change(10.0);
    setPosition((getPosition() += getSpeed() * dt));
    if (getPosition().y < 0) {
        getPosition().y = 0;
    } else if (getPosition().y + getHeight() > WINDOW_HEIGHT * 3) {
        getPosition().y = WINDOW_HEIGHT * 3 - getHeight();
    }
}
