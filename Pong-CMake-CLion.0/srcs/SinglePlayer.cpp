#include "Play.hpp"

void            SinglePlayer::Init() {
    setIfRunning(true);
    setWinner({"* Winner Left Player *", "* Winner Bot *"});
    setPlayMenu({"Continue", "Restart", "Exit to menu", "* ", " *"});
    this->key[Key::KeyPous] = false;
    setStringText({"esc", "/" + to_string(getPongInit().ScoreMax), "/" + to_string(getPongInit().ScoreMax)});
    getBackground().loadObject(getRenderer(), getPongInit().PathBackgrounds[getPongInit().NumPathBackground - 1]);
    if (getBackground().getObject()) {
        getBackground().Init(WINDOW_HEIGHT * 3, WINDOW_WIDTH * 5, Vect(0, 0));
        if (this->FirstPlayer.loadObject(getRenderer(), getPongInit().PathLeftRacket[getPongInit().NumPathLeftRacket - 1])) {
            this->FirstPlayer.Init(RACKET_HEIGHT, RACKET_WIDTH, Vect(15, WINDOW_HEIGHT * 3 / 2 - (RACKET_HEIGHT / 2)), Vect(0, 0));
            if (getBot().loadObject(getRenderer(), getPongInit().PathRightRacket[getPongInit().NumPathRightRacket - 1])) {
                getBot().setMaxSpeed(getPongInit().RacketSpeed);
                getBot().Init(RACKET_HEIGHT, RACKET_WIDTH, Vect(WINDOW_WIDTH * 5 - 15 - RACKET_WIDTH, WINDOW_HEIGHT * 3 / 2 - (RACKET_HEIGHT / 2)), Vect(0, 0));
                if (getBall().loadObject(getRenderer(), getPongInit().PathBalls[getPongInit().NumPathBalls - 1])) {
                    getBall().Init(30, 30, Vect(WINDOW_WIDTH * 5 / 2 - (30 / 2), WINDOW_HEIGHT * 3 / 2 - (30 / 2)), Vect(getPongInit().MaxBallSpeed_x, 0));
                    getBot().SearchPlaceHard(getBall(), dTime / 4);
                    if (!LoadAllText(45)) {
                        cout << "Error:Multiplayer::Init: load All Text" << SDL_GetError() << endl;
                        setIfRunning(false);
                    }
                } else {
                    setIfRunning(false);
                    cout << "Error:Multiplayer::Init: load Ball" << SDL_GetError() << endl;
                }
            } else {
                setIfRunning(false);
                cout << "Error:Multiplayer::Init: load SecondPlayer" << SDL_GetError() << endl;
            }
        } else {
            setIfRunning(false);
            cout << "Error:Multiplayer::Init: load FirstPlayer" << SDL_GetError() << endl;
        }
    } else {
        cout << "Error:Multiplayer::Init: load Background" << SDL_GetError() << endl;
        setIfRunning(false);
    }
}

bool            SinglePlayer::Events() {
    SDL_Event   event;
    this->startTime = std::chrono::high_resolution_clock::now();
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT :
                setIfRunning(false);
                setIfExit(true);
                break;
            case SDL_KEYDOWN : {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE : {
                        this->key[Key::KeyEsc] = true;
                        break;
                    }
                    case SDLK_w : {
                        if (!this->key[Key::KeyPous])
                            this->key[Key::Key1Up] = true;
                        break;
                    }
                    case SDLK_s : {
                        if (!this->key[Key::KeyPous])
                            this->key[Key::Key1Down] = true;
                        break;
                    }
                    case SDLK_SPACE : {
                        this->key[Key::KeyPous] = !this->key[Key::KeyPous];
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            case SDL_KEYUP : {
                switch (event.key.keysym.sym) {
                    case SDLK_w : {
                        this->key[Key::Key1Up] = false;
                        break;
                    }
                    case SDLK_s : {
                        this->key[Key::Key1Down] = false;
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            default:
                break;
        }
    }
    return true ;
}

void            SinglePlayer::Update() {
    if (this->key[Key::KeyPous])
        return ;
    if (key[Key::Key1Up]) {
        this->FirstPlayer.UpdateSpeed(-getPongInit().RacketSpeed);
    } else if (key[Key::Key1Down]) {
        this->FirstPlayer.UpdateSpeed(getPongInit().RacketSpeed);
    } else {
        this->FirstPlayer.UpdateSpeed(0);
    }
    this->FirstPlayer.Update(this->dTime / 4);
    getBot().Update(this->dTime / 4);
    if (getBall().Update(this->dTime / 4, this->FirstPlayer.getPosition(), getBot().getPosition(),
                      this->FirstPlayer.getSpeed(), getBot().getSpeed(), getPongInit())) {
        getBot().SearchPlaceHard(getBall(), this->dTime / 4);
    }
    UpdateInscription(2, 45);
}

void            SinglePlayer::MouseButtonDown(int i) {
    if (i == 1) {
        this->key[Key::KeyEsc] = false;
    } else if (i == 2) {
        getBall().setScoreFirst(0);
        getBall().setScoreSecond(0);
        getBall().Init(30, 30, Vect(WINDOW_WIDTH * 5 / 2 - (30 / 2), WINDOW_HEIGHT * 3 / 2 - (30 / 2)), Vect(getPongInit().MaxBallSpeed_x, 0));
        this->FirstPlayer.Init(RACKET_HEIGHT, RACKET_WIDTH, Vect(15, WINDOW_HEIGHT * 3 / 2 - (RACKET_HEIGHT / 2)), Vect(0, 0));
        getBot().Init(RACKET_HEIGHT, RACKET_WIDTH, Vect(WINDOW_WIDTH * 5 - 15 - RACKET_WIDTH, WINDOW_HEIGHT * 3 / 2 - (RACKET_HEIGHT / 2)), Vect(0, 0));
        getBot().SearchPlaceHard(getBall(), this->dTime / 4);
        this->key[Key::Key1Up] = false;
        this->key[Key::Key1Down] = false;
        this->key[Key::KeyEsc] = false;
    } else if (i == 3) {
        this->key[Key::KeyEsc] = false;
        setIfRunning(false);
    }
}

void            SinglePlayer::Renderer() {
    if (this->key[Key::KeyPous])
        return ;
    SDL_RenderClear(getRenderer());
    getBackground().Draw(getRenderer());
    this->FirstPlayer.Draw(getRenderer());
    getBot().Draw(getRenderer());
    getBall().Draw(getRenderer());
    DrawAllText();
    SDL_RenderPresent(getRenderer());
    this->stopTime = std::chrono::high_resolution_clock::now();
    this->dTime = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
}
