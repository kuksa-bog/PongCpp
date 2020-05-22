#include "../include/Play.hpp"

void Bot::SearchPlaceHard(Ball &ball, wind &w, float dt) {
    float s_x, s_y, p_x, p_y;
    bool r = true;
    s_x = ball.speed.x;
    s_y = ball.speed.y;
    p_x = ball.position.x;
    p_y = ball.position.y;
    while (p_x + w.ball_width / 2 < this->position.x - w.racket_width / 2) {
        p_x += s_x * dt;
        if ((p_y - w.ball_height / 2 < 0.0f)
            || (p_y + w.ball_height / 2 > WINDOW_HEIGHT)) {
            p_y += (p_y - w.ball_height / 2 < 0.0f) ? -(p_y - w.ball_width / 2)
                    : (WINDOW_HEIGHT - p_y - w.ball_width / 2);
            s_y = -s_y;
            r = false;
        }
        if (r)
            p_y += s_y * dt;
        r = true;
    }
    this->x1 = p_x;
    this->y1 = p_y;
}

void Bot::MoveToPlace(float dt) {
    if (this->position.y + dt * RACKET_SPEED < this->y2) {
        this->speed.y = RACKET_SPEED;
    } else if (this->position.y - dt * RACKET_SPEED > this->y2) {
        this->speed.y = -RACKET_SPEED;
    } else {
        this->speed.y = 0.0f;
    }
}

int Bot::Without_Change(float dt) {
    this->x2 = this->x1;
    this->y2 = this->y1;
    Bot::MoveToPlace(dt);
    return 1;
}

void Bot::Update(float dt, int y) {
    (this->Flag == 1) ? Without_Change(10.0) : 0;
    position += speed * dt;
    if (position.y - y / 2 < 0) {
        position.y = y / 2;
    } else if (position.y + y / 2 > (WINDOW_HEIGHT)) {
        position.y = WINDOW_HEIGHT - y / 2;
    }
}

