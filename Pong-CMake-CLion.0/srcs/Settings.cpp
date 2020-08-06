#include "Play.hpp"

void    Settings::Init() {
    setIfRunning(true);
    setStringText({"Settings", "Racket Speed:", "1", "2", "3", "4", "5",
                   "Max Ball Speed-x:", "1", "2", "3", "4", "5",
                   "Max Ball Speed-y:", "1", "2", "3", "4", "5",
                   "Max Score:", "10", "20", "30", "40", "50",
                   "Set Ball:", "1", "2", "3", "4", "5",
                                "6", "7", "8", "9", "10",
                                "11", "12", "13", "14", "15",
                   "Set Background:",
                   "Set Racket-1:", "1", "2", "3", "4", "5",
                   "Set Racket-2:", "1", "2", "3", "4", "5",
                   "Save & Exit to menu", "* ", " *"});
    getBackground().loadObject(getRenderer(), getPongInit().PathBackgrounds[getPongInit().NumPathBackground - 1]);
    if (getBackground().getObject()) {
        getBackground().Init(WINDOW_HEIGHT * 3, WINDOW_WIDTH * 5, Vect(0, 0));
        if (!LoadAllText(35) || !LoadAllBalls() || !LoadMapBackground() || !LoadAllLeftRackets() || !LoadAllRightRackets()) {
            cout << "Error:PongMenu::Init: load" << SDL_GetError() << endl;
            setIfRunning(false);
        }
    } else {
        cout << "Error:Settings::Init: load Background" << SDL_GetError() << endl;
        setIfRunning(false);
    }
}

bool    Settings::Events() {
    SDL_Event   event;
    SDL_WaitEvent(&event);
    switch (event.type) {
        case SDL_QUIT :
            setIfRunning(false);
            setIfExit(true);
            break ;
        case SDL_KEYDOWN : {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE :
                    setIfRunning(false);
                    break;
                default:
                    break ;
            }
            break;
        }
        case SDL_MOUSEWHEEL : {
            if (event.wheel.y > 0) {
                ScrollUpdate(true);
            } else if (event.wheel.y < 0) {
                ScrollUpdate(false);
            }

            if (getObjectText()[3].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 3) ? 3 : 59;                            // 1
            } else if (getObjectText()[4].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 4) ? 4 : 59;                            // 2
            } else if (getObjectText()[5].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 5) ? 5 : 59;                            // 3
            } else if (getObjectText()[6].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 6) ? 6 : 59;                            // 4
            } else if (getObjectText()[7].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 7) ? 7 : 59;                            // 5
            } else if (getObjectText()[9].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 9) ? 9 : 59;                            // 1
            } else if (getObjectText()[10].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 10) ? 10 : 59;                            // 2
            } else if (getObjectText()[11].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 11) ? 11 : 59;                            // 3
            } else if (getObjectText()[12].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 12) ? 12 : 59;                            // 4
            } else if (getObjectText()[13].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 13) ? 13 : 59;                            // 5
            } else if (getObjectText()[15].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 15) ? 15 : 59;                            // 1
            } else if (getObjectText()[16].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 16) ? 16 : 59;                            // 2
            } else if (getObjectText()[17].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 17) ? 17 : 59;                            // 3
            } else if (getObjectText()[18].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 18) ? 18 : 59;                            // 4
            } else if (getObjectText()[19].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 19) ? 19 : 59;                            // 5
            } else if (getObjectText()[21].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 21) ? 21 : 59;                            // 10
            } else if (getObjectText()[22].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 22) ? 22 : 59;                            // 20
            } else if (getObjectText()[23].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 23) ? 23 : 59;                            // 30
            } else if (getObjectText()[24].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 24) ? 24 : 59;                            // 40
            } else if (getObjectText()[25].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 25) ? 25 : 59;                            // 50
            } else if (getObjectText()[27].ifPositionObject(this->xMouseset, this->yMouseset)
            || getObjectBalls()[1].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 27) ? 27 : 59;                            // 1
            } else if (getObjectText()[28].ifPositionObject(this->xMouseset, this->yMouseset)
            || getObjectBalls()[2].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 28) ? 28 : 59;                            // 2
            } else if (getObjectText()[29].ifPositionObject(this->xMouseset, this->yMouseset)
            || getObjectBalls()[3].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 29) ? 29 : 59;                            // 3
            } else if (getObjectText()[30].ifPositionObject(this->xMouseset, this->yMouseset)
            || getObjectBalls()[4].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 30) ? 30 : 59;                            // 4
            } else if (getObjectText()[31].ifPositionObject(this->xMouseset, this->yMouseset)
            || getObjectBalls()[5].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 31) ? 31 : 59;                            // 5
            } else if (getObjectText()[32].ifPositionObject(this->xMouseset, this->yMouseset)
            || getObjectBalls()[6].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 32) ? 32 : 59;                            // 6
            } else if (getObjectText()[33].ifPositionObject(this->xMouseset, this->yMouseset)
            || getObjectBalls()[7].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 33) ? 33 : 59;                            // 7
            } else if (getObjectText()[34].ifPositionObject(this->xMouseset, this->yMouseset)
            || getObjectBalls()[8].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 34) ? 34 : 59;                            // 8
            } else if (getObjectText()[35].ifPositionObject(this->xMouseset, this->yMouseset)
            || getObjectBalls()[9].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 35) ? 35 : 59;                            // 9
            } else if (getObjectText()[36].ifPositionObject(this->xMouseset, this->yMouseset)
            || getObjectBalls()[10].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 36) ? 36 : 59;                            // 10
            } else if (getObjectText()[37].ifPositionObject(this->xMouseset, this->yMouseset)
            || getObjectBalls()[11].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 37) ? 37 : 59;                            // 11
            } else if (getObjectText()[38].ifPositionObject(this->xMouseset, this->yMouseset)
            || getObjectBalls()[12].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 38) ? 38 : 59;                            // 12
            } else if (getObjectText()[39].ifPositionObject(this->xMouseset, this->yMouseset)
            || getObjectBalls()[13].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 39) ? 39 : 59;                            // 13
            } else if (getObjectText()[40].ifPositionObject(this->xMouseset, this->yMouseset)
            || getObjectBalls()[14].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 40) ? 40 : 59;                            // 14
            } else if (getObjectText()[41].ifPositionObject(this->xMouseset, this->yMouseset)
            || getObjectBalls()[15].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 41) ? 41 : 59;                            // 15
            } else if (getObjectText()[44].ifPositionObject(this->xMouseset, this->yMouseset)
            || getObjectRacketLeft()[1].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 44) ? 44 : 59;                            // 1
            } else if (getObjectText()[45].ifPositionObject(this->xMouseset, this->yMouseset)
            || getObjectRacketLeft()[1].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 45) ? 45 : 59;                            // 2
            } else if (getObjectText()[46].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 46) ? 46 : 59;                            // 3
            } else if (getObjectText()[47].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 47) ? 47 : 59;                            // 4
            } else if (getObjectText()[48].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 48) ? 48 : 59;                            // 5
            } else if (getObjectText()[50].ifPositionObject(this->xMouseset, this->yMouseset)
            || getObjectRacketLeft()[1].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 50) ? 50 : 59;                            // 1
            } else if (getObjectText()[51].ifPositionObject(this->xMouseset, this->yMouseset)
            || getObjectRacketLeft()[1].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 51) ? 51 : 59;                            // 2
            } else if (getObjectText()[52].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 52) ? 52 : 59;                            // 3
            } else if (getObjectText()[53].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 53) ? 53 : 59;                            // 4
            } else if (getObjectText()[54].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 54) ? 54 : 59;                            // 5
            } else if (getObjectText()[55].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 55) ? 55 : 59;                            // Exit
            } else if (getMapBackground()[1].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 56) ? 56 : 59;                            // back1
            } else if (getMapBackground()[2].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 57) ? 57 : 59;                            // back2
            } else if (getMapBackground()[3].ifPositionObject(this->xMouseset, this->yMouseset)) {
                this->CaseNumber = (this->CaseNumber != 58) ? 58 : 59;                            // back3
            } else {
                this->CaseNumber = 0;
            }
        }
        case SDL_MOUSEBUTTONDOWN : {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                int xMouse = event.button.x, yMouse = event.button.y;
                if (getObjectText()[3].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(1, 2, getPongInit().RacketSpeed);
                } else if (getObjectText()[4].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(2, 2, getPongInit().RacketSpeed);
                } else if (getObjectText()[5].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(3, 2, getPongInit().RacketSpeed);
                } else if (getObjectText()[6].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(4, 2, getPongInit().RacketSpeed);
                } else if (getObjectText()[7].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(5, 2, getPongInit().RacketSpeed);
                } else if (getObjectText()[9].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(1, 8, getPongInit().MaxBallSpeed_x);
                } else if (getObjectText()[10].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(2, 8, getPongInit().MaxBallSpeed_x);
                } else if (getObjectText()[11].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(3, 8, getPongInit().MaxBallSpeed_x);
                } else if (getObjectText()[12].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(4, 8, getPongInit().MaxBallSpeed_x);
                } else if (getObjectText()[13].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(5, 8, getPongInit().MaxBallSpeed_x);
                } else if (getObjectText()[15].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(1, 14, getPongInit().MaxBallSpeed_y);
                } else if (getObjectText()[16].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(2, 14, getPongInit().MaxBallSpeed_y);
                } else if (getObjectText()[17].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(3, 14, getPongInit().MaxBallSpeed_y);
                } else if (getObjectText()[18].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(4, 14, getPongInit().MaxBallSpeed_y);
                } else if (getObjectText()[19].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(5, 14, getPongInit().MaxBallSpeed_y);
                } else if (getObjectText()[21].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInitScore(1, 20, getPongInit().ScoreMax);
                } else if (getObjectText()[22].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInitScore(2, 20, getPongInit().ScoreMax);
                } else if (getObjectText()[23].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInitScore(3, 20, getPongInit().ScoreMax);
                } else if (getObjectText()[24].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInitScore(4, 20, getPongInit().ScoreMax);
                } else if (getObjectText()[25].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInitScore(5, 20, getPongInit().ScoreMax);
                } else if (getObjectText()[27].ifPositionObject(xMouse, yMouse)
                || getObjectBalls()[1].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(1, 26, getPongInit().NumPathBalls);
                } else if (getObjectText()[28].ifPositionObject(xMouse, yMouse)
                || getObjectBalls()[2].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(2, 26, getPongInit().NumPathBalls);
                } else if (getObjectText()[29].ifPositionObject(xMouse, yMouse)
                || getObjectBalls()[3].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(3, 26, getPongInit().NumPathBalls);
                } else if (getObjectText()[30].ifPositionObject(xMouse, yMouse)
                || getObjectBalls()[4].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(4, 26, getPongInit().NumPathBalls);
                } else if (getObjectText()[31].ifPositionObject(xMouse, yMouse)
                || getObjectBalls()[5].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(5, 26, getPongInit().NumPathBalls);
                } else if (getObjectText()[32].ifPositionObject(xMouse, yMouse)
                || getObjectBalls()[6].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(6, 26, getPongInit().NumPathBalls);
                } else if (getObjectText()[33].ifPositionObject(xMouse, yMouse)
                || getObjectBalls()[7].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(7, 26, getPongInit().NumPathBalls);
                } else if (getObjectText()[34].ifPositionObject(xMouse, yMouse)
                || getObjectBalls()[8].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(8, 26, getPongInit().NumPathBalls);
                } else if (getObjectText()[35].ifPositionObject(xMouse, yMouse)
                || getObjectBalls()[9].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(9, 26, getPongInit().NumPathBalls);
                } else if (getObjectText()[36].ifPositionObject(xMouse, yMouse)
                || getObjectBalls()[10].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(10, 26, getPongInit().NumPathBalls);
                } else if (getObjectText()[37].ifPositionObject(xMouse, yMouse)
                || getObjectBalls()[11].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(11, 26, getPongInit().NumPathBalls);
                } else if (getObjectText()[38].ifPositionObject(xMouse, yMouse)
                || getObjectBalls()[12].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(12, 26, getPongInit().NumPathBalls);
                } else if (getObjectText()[39].ifPositionObject(xMouse, yMouse)
                || getObjectBalls()[13].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(13, 26, getPongInit().NumPathBalls);
                } else if (getObjectText()[40].ifPositionObject(xMouse, yMouse)
                || getObjectBalls()[14].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(14, 26, getPongInit().NumPathBalls);
                } else if (getObjectText()[41].ifPositionObject(xMouse, yMouse)
                || getObjectBalls()[15].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(15, 26, getPongInit().NumPathBalls);
                } else if (getObjectText()[44].ifPositionObject(xMouse, yMouse)
                || getObjectRacketLeft()[1].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(1, 43, getPongInit().NumPathLeftRacket);
                } else if (getObjectText()[45].ifPositionObject(xMouse, yMouse)
                || getObjectRacketLeft()[2].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(2, 43, getPongInit().NumPathLeftRacket);
                } else if (getObjectText()[50].ifPositionObject(xMouse, yMouse)
                || getObjectRacketRight()[1].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(1, 49, getPongInit().NumPathRightRacket);
                } else if (getObjectText()[51].ifPositionObject(xMouse, yMouse)
                || getObjectRacketRight()[2].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInit(2, 49, getPongInit().NumPathRightRacket);
                } else if (getMapBackground()[1].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInitBackground(1, getPongInit().NumPathBackground);
                } else if (getMapBackground()[2].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInitBackground(2, getPongInit().NumPathBackground);
                } else if (getMapBackground()[3].ifPositionObject(xMouse, yMouse)) {
                    UpdatePongInitBackground(3, getPongInit().NumPathBackground);
                } else if (getObjectText()[55].ifPositionObject(xMouse, yMouse)) {
                    setIfRunning(false);
                }
            }
            break;
        }
        case SDL_MOUSEMOTION : {
            int xMouse, yMouse;
            SDL_GetMouseState(&xMouse, &yMouse);
            this->xMouseset = xMouse; this->yMouseset = yMouse;
            if (getObjectText()[3].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 3) ? 3 : 59;                            // 1
            } else if (getObjectText()[4].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 4) ? 4 : 59;                            // 2
            } else if (getObjectText()[5].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 5) ? 5 : 59;                            // 3
            } else if (getObjectText()[6].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 6) ? 6 : 59;                            // 4
            } else if (getObjectText()[7].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 7) ? 7 : 59;                            // 5
            } else if (getObjectText()[9].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 9) ? 9 : 59;                            // 1
            } else if (getObjectText()[10].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 10) ? 10 : 59;                            // 2
            } else if (getObjectText()[11].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 11) ? 11 : 59;                            // 3
            } else if (getObjectText()[12].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 12) ? 12 : 59;                            // 4
            } else if (getObjectText()[13].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 13) ? 13 : 59;                            // 5
            } else if (getObjectText()[15].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 15) ? 15 : 59;                            // 1
            } else if (getObjectText()[16].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 16) ? 16 : 59;                            // 2
            } else if (getObjectText()[17].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 17) ? 17 : 59;                            // 3
            } else if (getObjectText()[18].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 18) ? 18 : 59;                            // 4
            } else if (getObjectText()[19].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 19) ? 19 : 59;                            // 5
            } else if (getObjectText()[21].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 21) ? 21 : 59;                            // 10
            } else if (getObjectText()[22].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 22) ? 22 : 59;                            // 20
            } else if (getObjectText()[23].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 23) ? 23 : 59;                            // 30
            } else if (getObjectText()[24].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 24) ? 24 : 59;                            // 40
            } else if (getObjectText()[25].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 25) ? 25 : 59;                            // 50
            } else if (getObjectText()[27].ifPositionObject(xMouse, yMouse)
            || getObjectBalls()[1].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 27) ? 27 : 59;                            // 1
            } else if (getObjectText()[28].ifPositionObject(xMouse, yMouse)
            || getObjectBalls()[2].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 28) ? 28 : 59;                            // 2
            } else if (getObjectText()[29].ifPositionObject(xMouse, yMouse)
            || getObjectBalls()[3].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 29) ? 29 : 59;                            // 3
            } else if (getObjectText()[30].ifPositionObject(xMouse, yMouse)
            || getObjectBalls()[4].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 30) ? 30 : 59;                            // 4
            } else if (getObjectText()[31].ifPositionObject(xMouse, yMouse)
            || getObjectBalls()[5].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 31) ? 31 : 59;                            // 5
            } else if (getObjectText()[32].ifPositionObject(xMouse, yMouse)
            || getObjectBalls()[6].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 32) ? 32 : 59;                            // 6
            } else if (getObjectText()[33].ifPositionObject(xMouse, yMouse)
            || getObjectBalls()[7].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 33) ? 33 : 59;                            // 7
            } else if (getObjectText()[34].ifPositionObject(xMouse, yMouse)
            || getObjectBalls()[8].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 34) ? 34 : 59;                            // 8
            } else if (getObjectText()[35].ifPositionObject(xMouse, yMouse)
            || getObjectBalls()[9].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 35) ? 35 : 59;                            // 9
            } else if (getObjectText()[36].ifPositionObject(xMouse, yMouse)
            || getObjectBalls()[10].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 36) ? 36 : 59;                            // 10
            } else if (getObjectText()[37].ifPositionObject(xMouse, yMouse)
            || getObjectBalls()[11].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 37) ? 37 : 59;                            // 11
            } else if (getObjectText()[38].ifPositionObject(xMouse, yMouse)
            || getObjectBalls()[12].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 38) ? 38 : 59;                            // 12
            } else if (getObjectText()[39].ifPositionObject(xMouse, yMouse)
            || getObjectBalls()[13].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 39) ? 39 : 59;                            // 13
            } else if (getObjectText()[40].ifPositionObject(xMouse, yMouse)
            || getObjectBalls()[14].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 40) ? 40 : 59;                            // 14
            } else if (getObjectText()[41].ifPositionObject(xMouse, yMouse)
            || getObjectBalls()[15].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 41) ? 41 : 59;                            // 15
            } else if (getObjectText()[44].ifPositionObject(xMouse, yMouse)
            || getObjectRacketLeft()[1].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 44) ? 44 : 59;                            // 1
            } else if (getObjectText()[45].ifPositionObject(xMouse, yMouse)
            || getObjectRacketLeft()[2].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 45) ? 45 : 59;                            // 2
            } else if (getObjectText()[46].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 46) ? 46 : 59;                            // 3
            } else if (getObjectText()[47].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 47) ? 47 : 59;                            // 4
            } else if (getObjectText()[48].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 48) ? 48 : 59;                            // 5
            } else if (getObjectText()[50].ifPositionObject(xMouse, yMouse)
            || getObjectRacketRight()[1].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 50) ? 50 : 59;                            // 1
            } else if (getObjectText()[51].ifPositionObject(xMouse, yMouse)
            || getObjectRacketRight()[2].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 51) ? 51 : 59;                            // 2
            } else if (getObjectText()[52].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 52) ? 52 : 59;                            // 3
            } else if (getObjectText()[53].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 53) ? 53 : 59;                            // 4
            } else if (getObjectText()[54].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 54) ? 54 : 59;                            // 5
            } else if (getObjectText()[55].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 55) ? 55 : 59;                            // Exit
            } else if (getMapBackground()[1].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 56) ? 56 : 59;                            // back1
            } else if (getMapBackground()[2].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 57) ? 57 : 59;                            // back2
            } else if (getMapBackground()[3].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 58) ? 58 : 59;                            // back3
            } else {
                this->CaseNumber = 0;
            }
            break ;
        }
        default:
            break ;
    }
    return true ;
}







void            Settings::InitText(int ind) {
    int x = WINDOW_WIDTH * 5 / 2, y = WINDOW_HEIGHT * 3 / 15;
    int iW, iH;
    SDL_QueryTexture(getObjectText()[ind].getObject(), nullptr, nullptr, &iW, &iH);
    if (ind == 1)
        getObjectText()[ind].Init(iH, iW, {(x - (iW / 2)), (y * ind - (iH / 2))});
    else if (ind > 1 && ind <= 7) {
        int i = ind - 1, x2 = WINDOW_WIDTH * 5 / 9;
        if (i == 1)
            getObjectText()[ind].Init(iH, iW, {(x2 * (i + 1) - (iW / 2)), (y * 3 - (iH / 2))});
        else
            getObjectText()[ind].Init(iH, iW, {(x2 * (i + 2) - (iW / 2)), (y * 3 - (iH / 2))});
    } else if (ind > 7 && ind <= 13) {
        int i = ind - 7, x2 = WINDOW_WIDTH * 5 / 9;
        if (i == 1)
            getObjectText()[ind].Init(iH, iW, {(x2 * (i + 1) - (iW / 2)), (y * 4 - (iH / 2))});
        else
            getObjectText()[ind].Init(iH, iW, {(x2 * (i + 2) - (iW / 2)), (y * 4 - (iH / 2))});
    } else if (ind > 13 && ind <= 19) {
        int i = ind - 13, x2 = WINDOW_WIDTH * 5 / 9;
        if (i == 1)
            getObjectText()[ind].Init(iH, iW, {(x2 * (i + 1) - (iW / 2)), (y * 5 - (iH / 2))});
        else
            getObjectText()[ind].Init(iH, iW, {(x2 * (i + 2) - (iW / 2)), (y * 5 - (iH / 2))});
    } else if (ind > 19 && ind <= 25) {
        int i = ind - 19, x2 = WINDOW_WIDTH * 5 / 9;
        if (i == 1)
            getObjectText()[ind].Init(iH, iW, {(x2 * (i + 1) - (iW / 2)), (y * 6 - (iH / 2))});
        else
            getObjectText()[ind].Init(iH, iW, {(x2 * (i + 2) - (iW / 2) - 10), (y * 6 - (iH / 2))});
    } else if (ind > 25 && ind <= 31) {
        int i = ind - 25, x2 = WINDOW_WIDTH * 5 / 9;
        if (i == 1)
            getObjectText()[ind].Init(iH, iW, {(x2 * (i + 1) - (iW / 2)), (y * 7 - (iH / 2))});
        else
            getObjectText()[ind].Init(iH, iW, {(x2 * (i + 2) - (iW / 2)), (y * 7 - (iH / 2))});
    } else if (ind > 31 && ind <= 36) {
        int i = ind - 31, x2 = WINDOW_WIDTH * 5 / 9;
        if (i < 5)
            getObjectText()[ind].Init(iH, iW, {(x2 * (i + 3) - (iW / 2)), (y * 8 - (iH / 2))});
        else
            getObjectText()[ind].Init(iH, iW, {(x2 * (i + 3) - (iW / 2) - 10), (y * 8 - (iH / 2))});

    } else if (ind > 36 && ind <= 41) {
        int i = ind - 36, x2 = WINDOW_WIDTH * 5 / 9;
        getObjectText()[ind].Init(iH, iW, {(x2 * (i + 3) - (iW / 2) - 10), (y * 9 - (iH / 2))});
    } else if (ind > 41 && ind <= 42) {
        int i = ind - 41, x2 = WINDOW_WIDTH * 5 / 9;
        getObjectText()[ind].Init(iH, iW, {(x2 * (i + 1) - (iW / 2)), (y * 10 - (iH / 2))});
    } else if (ind > 42 && ind <= 48) {
        int i = ind - 42, x2 = WINDOW_WIDTH * 5 / 9;
        if (i == 1)
            getObjectText()[ind].Init(iH, iW, {(x2 * (i + 1) - (iW / 2)), (y * 14 - (iH / 2))});
        else
            getObjectText()[ind].Init(iH, iW, {(x2 * (i + 2) - (iW / 2)), (y * 14 - (iH / 2))});
    } else if (ind > 48 && ind <= 54) {
        int i = ind - 48, x2 = WINDOW_WIDTH * 5 / 9;
        if (i == 1)
            getObjectText()[ind].Init(iH, iW, {(x2 * (i + 1) - (iW / 2)), (y * 17 - (iH / 2))});
        else
            getObjectText()[ind].Init(iH, iW, {(x2 * (i + 2) - (iW / 2)), (y * 17 - (iH / 2))});
    } else if (ind == 55) {
        getObjectText()[ind].Init(iH, iW, {(x - (iW / 2)), (y * 19 - (iH / 2))});
    }
}

bool            Settings::LoadAllText(int size) {
    int i = 1;
    for (const string &s : getStringText()) {
        if (i <= 54) {
            if (i - 2 == getPongInit().RacketSpeed || i - 8 == getPongInit().MaxBallSpeed_x
            || i - 14 == getPongInit().MaxBallSpeed_y || i - 20 == getPongInit().ScoreMax / 10
            || i - 26 == getPongInit().NumPathBalls || i - 43 == getPongInit().NumPathLeftRacket
            || i - 49 == getPongInit().NumPathRightRacket) {
                if (!getObjectText()[i].loadObjectTextSet3(getRenderer(), s, size))
                    return false ;
                InitText(i);
            } else {
                if (!getObjectText()[i].loadObjectTextSet1(getRenderer(), s, size))
                    return false ;
                InitText(i);
            }
        } else if (i == 55) {
            if (!getObjectText()[i].loadObjectTextSet1(getRenderer(), s, size))
                return false ;
            InitText(i);
        }
        i++;
    }
    return true;
}







void            Settings::InitBalls(int ind) {
    int x = WINDOW_WIDTH * 5 / 9, y = WINDOW_HEIGHT * 3 / 15, iW = 30, iH = 30;
    if (ind <= 5)
        getObjectBalls()[ind].Init(iH, iW, {(x * (ind + 3) - (iW / 2) + 40), (y * 7 - (iH / 2))});
    else if (ind > 5 && ind <= 10) {
        int i = ind - 5;
        getObjectBalls()[ind].Init(iH, iW, {(x * (i + 3) - (iW / 2) + 40), (y * 8 - (iH / 2))});
    } else {
        int i = ind - 10;
        getObjectBalls()[ind].Init(iH, iW, {(x * (i + 3) - (iW / 2) + 40), (y * 9 - (iH / 2))});
    }
}

bool            Settings::LoadAllBalls() {
    int i = 1;
    for (const string &s : getPongInit().PathBalls) {
        if (!getObjectBalls()[i].loadObject(getRenderer(), s))
            return false ;
        InitBalls(i);
        i++;
    }
    return true ;
}

void             Settings::DrawAllBalls() {
    for (auto& m : getObjectBalls()) {
        m.second.Draw(getRenderer());
    }
}







void            Settings::Renderer() {
    SDL_RenderClear(getRenderer());
    getBackground().Draw(getRenderer());
    DrawAllText();
    DrawAllBalls();
    DrawMapBackground();
    DrawAllLeftRackets();
    DrawAllRightRackets();
    SDL_RenderPresent(getRenderer());
}






void            Settings::InitMapBackground(int ind) {
    int x = WINDOW_WIDTH * 5 / 9, y = WINDOW_HEIGHT * 3 / 15, iW = 187, iH = 112;
    if (ind == 1) {
        getMapBackground()[ind].Init(iH, iW, {(x * (ind + 3) - 50), (y * 11 - (iH / 2))});
        getRectBackground()[ind].InitRectPong((y * 11 - (iH / 2) - 4), (x * (ind + 3) - 50 - 4), iH + 8, iW + 8);
    } else if (ind == 2) {
        getMapBackground()[ind].Init(iH, iW, {(x * (ind + 3) + 50), (y * 11 - (iH / 2))});
        getRectBackground()[ind].InitRectPong((y * 11 - (iH / 2) - 4), (x * (ind + 3) + 50 - 4), iH + 8, iW + 8);
    } else {
        getMapBackground()[ind].Init(iH, iW, {(x * (ind + 3) + 150), (y * 11 - (iH / 2))});
        getRectBackground()[ind].InitRectPong((y * 11 - (iH / 2) - 4), (x * (ind + 3) + 150 - 4), iH + 8, iW + 8);
    }
    getRectBackground()[ind].setColorSetNow(getRectBackground()[ind].getColorSet1());

}

bool            Settings::LoadMapBackground() {
    int i = 1;
    for (const string &s : getPongInit().PathBackgrounds) {
        if (!getMapBackground()[i].loadObject(getRenderer(), s))
            return false ;
        InitMapBackground(i);
        i++;
    }
    return true;
}

void             Settings::DrawMapBackground() {
    int i = 1;
    for (auto& m : getRectBackground()) {
        if (i == getPongInit().NumPathBackground) {
            m.second.setColorSetNow(m.second.getColorSet3());
            m.second.RenderFillRectPongSet(getRenderer());
        } else {
            m.second.RenderFillRectPongSet(getRenderer());
        }
        i++;
    }
    for (auto& m : getMapBackground()) {
        m.second.Draw(getRenderer());
    }
}






void            Settings::InitAllLeftRackets(int ind) {
    int x = WINDOW_WIDTH * 5 / 9, y = WINDOW_HEIGHT * 3 / 15, iW = 50, iH = 100;
    getObjectRacketLeft()[ind].Init(iH, iW, {(x * (ind + 3) - (iW / 2) + 50), (y * 13 - (iH / 2) + 20)});
}

bool            Settings::LoadAllLeftRackets() {
    int i = 1;
    for (const string &s : getPongInit().PathLeftRacket) {
        if (!getObjectRacketLeft()[i].loadObject(getRenderer(), s))
            return false ;
        InitAllLeftRackets(i);
        i++;
    }
    return true ;
}

void            Settings::DrawAllLeftRackets() {
    for (auto& m : getObjectRacketLeft()) {
        m.second.Draw(getRenderer());
    }
}





void            Settings::InitAllRightRackets(int ind) {
    int x = WINDOW_WIDTH * 5 / 9, y = WINDOW_HEIGHT * 3 / 15, iW = 50, iH = 100;
    getObjectRacketRight()[ind].Init(iH, iW, {(x * (ind + 3) - (iW / 2) + 50), (y * 16 - (iH / 2) + 20)});
}

bool            Settings::LoadAllRightRackets() {
    int i = 1;
    for (const string &s : getPongInit().PathRightRacket) {
        if (!getObjectRacketRight()[i].loadObject(getRenderer(), s))
            return false ;
        InitAllRightRackets(i);
        i++;
    }
    return true ;
}

void            Settings::DrawAllRightRackets() {
    for (auto& m : getObjectRacketRight()) {
        m.second.Draw(getRenderer());
    }
}





void            Settings::ScrollUpdate(bool scroll) {
    int scrollNow1 = (this->ScrollNum < this->MaxScroll) ? this->ScrollNum + this->ScrollMove : this->ScrollNum;
    int scrollNow2 = (this->ScrollNum > this->MinScroll) ? this->ScrollNum - this->ScrollMove : this->ScrollNum;
    if (scroll && scrollNow1 != this->ScrollNum) {
        for (auto& a : getRectBackground()) {
            a.second.getRectPong().y += this->ScrollMove;
        }
        for (auto& a : getMapBackground()) {
            a.second.getPosition().y += this->ScrollMove;
        }
        for (auto& a : getObjectBalls()) {
            a.second.getPosition().y += this->ScrollMove;
        }
        for (auto& a : getObjectRacketLeft()) {
            a.second.getPosition().y += this->ScrollMove;
        }
        for (auto& a : getObjectText()) {
            a.second.getPosition().y += this->ScrollMove;
        }
        for (auto& a : getObjectRacketRight()) {
            a.second.getPosition().y += this->ScrollMove;
        }
        this->ScrollNum += this->ScrollMove;
    } else if (!scroll && scrollNow2 != this->ScrollNum) {
        for (auto& a : getRectBackground()) {
            a.second.getRectPong().y -= this->ScrollMove;
        }
        for (auto& a : getMapBackground()) {
            a.second.getPosition().y -= this->ScrollMove;
        }
        for (auto& a : getObjectBalls()) {
            a.second.getPosition().y -= this->ScrollMove;
        }
        for (auto& a : getObjectRacketLeft()) {
            a.second.getPosition().y -= this->ScrollMove;
        }
        for (auto& a : getObjectText()) {
            a.second.getPosition().y -= this->ScrollMove;
        }
        for (auto& a : getObjectRacketRight()) {
            a.second.getPosition().y -= this->ScrollMove;
        }
        this->ScrollNum -= this->ScrollMove;
    }
}

void            Settings::UpdateInscription(int ind, int update) {
    if (update == 1) {
        getObjectText()[ind].UpdateSet(getRenderer(), getStringText()[ind - 1], 35, 1);
    } else if (update == 2) {
        getObjectText()[ind].UpdateSet(getRenderer(), getStringText()[ind - 1], 35, 2);
    } else if (update == 3) {
        this->RectBackground[ind].setColorSetNow(this->RectBackground[ind].getColorSet1());
    } else if (update == 4) {
        this->RectBackground[ind].setColorSetNow(this->RectBackground[ind].getColorSet2());
    } else if (update == 5) {
        getObjectText()[ind].UpdateSet(getRenderer(), getStringText()[55] + getStringText()[ind - 1] + getStringText()[56], 35, 2);
        int iW, iH;
        SDL_QueryTexture(getObjectText()[ind].getObject(), nullptr, nullptr, &iW, &iH);
        getObjectText()[ind].setWidth(iW);
        Vect v {WINDOW_WIDTH * 5 / 2 - (iW / 2), getObjectText()[ind].getPosition().y};
        getObjectText()[ind].setPosition(v);
    } else if (update == 6) {
        getObjectText()[ind].UpdateSet(getRenderer(), getStringText()[ind - 1], 35, 1);
        int iW, iH;
        SDL_QueryTexture(getObjectText()[ind].getObject(), nullptr, nullptr, &iW, &iH);
        getObjectText()[ind].setWidth(iW);
        Vect v {WINDOW_WIDTH * 5 / 2 - (iW / 2), getObjectText()[ind].getPosition().y};
        getObjectText()[ind].setPosition(v);
    }
}

void            Settings::Update() {
    if (     ((this->CaseNumber == 3 || this->CaseNumber == 4 || this->CaseNumber == 5
            || this->CaseNumber == 6 || this->CaseNumber == 7)
            && CaseNumber_static(this->CaseNumber - 2, getPongInit().RacketSpeed))
        ||   ((this->CaseNumber == 9 || this->CaseNumber == 10 || this->CaseNumber == 11
            || this->CaseNumber == 12 || this->CaseNumber == 13)
            && CaseNumber_static(this->CaseNumber - 8, getPongInit().MaxBallSpeed_x))
        ||   ((this->CaseNumber == 15 || this->CaseNumber == 16 || this->CaseNumber == 17
            || this->CaseNumber == 18 || this->CaseNumber == 19)
            && CaseNumber_static(this->CaseNumber - 14, getPongInit().MaxBallSpeed_y))
        ||   ((this->CaseNumber == 21 || this->CaseNumber == 22 || this->CaseNumber == 23
            || this->CaseNumber == 24 || this->CaseNumber == 25)
            && CaseNumber_static(this->CaseNumber - 20, getPongInit().ScoreMax / 10))
        ||   ((this->CaseNumber == 27 || this->CaseNumber == 28 || this->CaseNumber == 29
            || this->CaseNumber == 30 || this->CaseNumber == 31 || this->CaseNumber == 32
            || this->CaseNumber == 33 || this->CaseNumber == 34 || this->CaseNumber == 35
            || this->CaseNumber == 36 || this->CaseNumber == 37 || this->CaseNumber == 38
            || this->CaseNumber == 39 || this->CaseNumber == 40 || this->CaseNumber == 41)
            && CaseNumber_static(this->CaseNumber - 26, getPongInit().NumPathBalls))
        ||   ((this->CaseNumber == 44 || this->CaseNumber == 45 || this->CaseNumber == 46
            || this->CaseNumber == 47 || this->CaseNumber == 48)
            && CaseNumber_static(this->CaseNumber - 43, getPongInit().NumPathLeftRacket))
        ||   ((this->CaseNumber == 50 || this->CaseNumber == 51 || this->CaseNumber == 52
            || this->CaseNumber == 53 || this->CaseNumber == 54)
            && CaseNumber_static(this->CaseNumber - 49, getPongInit().NumPathRightRacket))) {
        UpdateMouseMotion(2);
    } else if (this->CaseNumber == 55) {
        UpdateMouseMotion(5);
    } else if (((this->CaseNumber == 56 || this->CaseNumber == 57 || this->CaseNumber == 58)
            && CaseNumber_static(this->CaseNumber - 55, getPongInit().NumPathBackground))) {
        UpdateMouseMotion(4);
    } else if      (this->InducedInscription != 0 && this->CaseNumber != 59) {
        if (this->InducedInscription == 55) {
            UpdateInscription(this->InducedInscription, 6);
        } else if ((this->InducedInscription == 56 || this->InducedInscription == 57 || this->InducedInscription == 58)
                && CaseNumber_static(this->InducedInscription - 55, getPongInit().NumPathBackground)) {
            UpdateInscription(this->InducedInscription - 55, 3);
        } else if ((this->InducedInscription >= 3 && this->InducedInscription <= 7 && CaseNumber_static(this->InducedInscription - 2, getPongInit().RacketSpeed))
                || (this->InducedInscription >= 9 && this->InducedInscription <= 13 && CaseNumber_static(this->InducedInscription - 8, getPongInit().MaxBallSpeed_x))
                || (this->InducedInscription >= 15 && this->InducedInscription <= 19 && CaseNumber_static(this->InducedInscription - 14, getPongInit().MaxBallSpeed_y))
                || (this->InducedInscription >= 21 && this->InducedInscription <= 25 && CaseNumber_static(this->InducedInscription - 20, getPongInit().ScoreMax / 10))
                || (this->InducedInscription >= 27 && this->InducedInscription <= 41 && CaseNumber_static(this->InducedInscription - 26, getPongInit().NumPathBalls))
                || (this->InducedInscription >= 44 && this->InducedInscription <= 45 && CaseNumber_static(this->InducedInscription - 43, getPongInit().NumPathLeftRacket))
                || (this->InducedInscription >= 50 && this->InducedInscription <= 51 && CaseNumber_static(this->InducedInscription - 49, getPongInit().NumPathRightRacket))
                || (this->InducedInscription > 51 && this->InducedInscription < 55)
                || (this->InducedInscription > 45 && this->InducedInscription < 49)) {
            UpdateInscription(this->InducedInscription, 1);
        }
        this->InducedInscription = 0;
    }
}


void               Settings::UpdatePongInit(int update, int toNumString, int& PongCase) {
    int ind = PongCase + toNumString;
    getObjectText()[ind].UpdateSet(getRenderer(), getStringText()[ind - 1], 35, 1);   // 1
    PongCase = update;
    ind = PongCase + toNumString;
    getObjectText()[ind].UpdateSet(getRenderer(), getStringText()[ind - 1], 35, 3);   // 1
};

void                Settings::UpdatePongInitScore(int update, int toNumString, int& PongCase) {
    int ind = PongCase / 10 + toNumString;
    getObjectText()[ind].UpdateSet(getRenderer(), getStringText()[ind - 1], 35, 1);   // 1
    PongCase = update * 10;
    ind = PongCase / 10 + toNumString;
    getObjectText()[ind].UpdateSet(getRenderer(), getStringText()[ind - 1], 35, 3);   // 1
};

void                Settings::UpdatePongInitBackground(int update, int& PongCase) {
    if (update == PongCase)
        return ;
    this->RectBackground[PongCase].setColorSetNow( this->RectBackground[PongCase].getColorSet1());
    PongCase = update;
    getBackground().CleanObject();
    getBackground().loadObject(getRenderer(), getPongInit().PathBackgrounds[PongCase - 1]);
};

void                Settings::UpdateMouseMotion(int update) {
    if (this->InducedInscription == 55) {
        UpdateInscription(this->InducedInscription, 6);
    } else if ((this->InducedInscription == 56 || this->InducedInscription == 57 || this->InducedInscription == 58)
               && CaseNumber_static(this->InducedInscription - 55, getPongInit().NumPathBackground)) {
        UpdateInscription(this->InducedInscription - 55, 3);
    } else if (this->InducedInscription != 0) {
        UpdateInscription(this->InducedInscription, 1);
    }
    this->InducedInscription = this->CaseNumber;
    if (this->InducedInscription == 56 || this->InducedInscription == 57 || this->InducedInscription == 58) {
        UpdateInscription(this->InducedInscription - 55, update);
    } else {
        UpdateInscription(this->InducedInscription, update);
    }
};

