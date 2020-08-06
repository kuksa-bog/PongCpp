#include "../includes/Object.hpp"

Racket:: Racket() {
    cout << "Racket created...." << endl;
}

void    Racket::Update(int dTime) {
    setPosition((getPosition() += getSpeed() * dTime));
    if (getPosition().y < 0) {
        getPosition().y = 0;
    } else if (getPosition().y + getHeight() > WINDOW_HEIGHT * 3) {
        getPosition().y = WINDOW_HEIGHT * 3 - getHeight();
    }
}

