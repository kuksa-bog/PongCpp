#include "Play.hpp"

bool        Multiplayer::Running() {
    Init();
    while (ifContinue()) {
        if (getBall().getScoreFirst() == getPongInit().ScoreMax
            || getBall().getScoreSecond() == getPongInit().ScoreMax) {
            if (LoadPlayMenu(45, false)) {
                this->key[Key::KeyEsc] = true;
                while (this->key[Key::KeyEsc]) {
                    Events2(true);
                    Renderer2();
                }
                this->startTime = std::chrono::high_resolution_clock::now();
                this->stopTime = std::chrono::high_resolution_clock::now();
                this->dTime = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
            }
        }
        Events();
        if (this->key[Key::KeyEsc]) {
            if (LoadPlayMenu(45, true)) {
                this->XContinue = true;
                while (this->key[Key::KeyEsc]) {
                    Events2(true);
                    Renderer2();
                }
                this->XContinue = false;
                this->startTime = std::chrono::high_resolution_clock::now();
                this->stopTime = std::chrono::high_resolution_clock::now();
                this->dTime = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
            }
        }
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

void            Multiplayer::Init() {
    setIfRunning(true);
    setWinner({"* Winner Left Player *", "* Winner Right Player *"});
    setPlayMenu({"Continue", "Restart", "Exit to menu", "* ", " *"});
    this->key[Key::KeyPous] = false;
    setStringText({"esc", "/" + to_string(getPongInit().ScoreMax), "/" + to_string(getPongInit().ScoreMax)});
    getBackground().loadObject(getRenderer(), getPongInit().PathBackgrounds[getPongInit().NumPathBackground - 1]);
    if (getBackground().getObject()) {
        getBackground().Init(WINDOW_HEIGHT * 3, WINDOW_WIDTH * 5, Vect(0, 0));
        if (this->FirstPlayer.loadObject(getRenderer(), getPongInit().PathLeftRacket[getPongInit().NumPathLeftRacket - 1])) {
            this->FirstPlayer.Init(RACKET_HEIGHT, RACKET_WIDTH, Vect(15, WINDOW_HEIGHT * 3 / 2 - (RACKET_HEIGHT / 2)), Vect(0, 0));
            if (this->SecondPlayer.loadObject(getRenderer(), getPongInit().PathRightRacket[getPongInit().NumPathRightRacket - 1])) {
                this->SecondPlayer.Init(RACKET_HEIGHT, RACKET_WIDTH, Vect(WINDOW_WIDTH * 5 - 15 - RACKET_WIDTH, WINDOW_HEIGHT * 3 / 2 - (RACKET_HEIGHT / 2)), Vect(0, 0));
                if (this->getBall().loadObject(getRenderer(), getPongInit().PathBalls[getPongInit().NumPathBalls - 1])) {
                    this->getBall().Init(30, 30, Vect(WINDOW_WIDTH * 5 / 2 - (30 / 2), WINDOW_HEIGHT * 3 / 2 - (30 / 2)), Vect(getPongInit().MaxBallSpeed_x, 0));
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


bool            Multiplayer::Events() {
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
                    case SDLK_UP : {
                        if (!this->key[Key::KeyPous])
                            this->key[Key::Key2Up] = true;
                        break;
                    }
                    case SDLK_DOWN : {
                        if (!this->key[Key::KeyPous])
                            this->key[Key::Key2Down] = true;
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
                    case SDLK_UP : {
                        this->key[Key::Key2Up] = false;
                        break;
                    }
                    case SDLK_DOWN : {
                        this->key[Key::Key2Down] = false;
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

void            Multiplayer::Update() {
    if (this->key[Key::KeyPous])
        return ;
    if (key[Key::Key1Up]) {
        this->FirstPlayer.UpdateSpeed(-getPongInit().RacketSpeed);
    } else if (key[Key::Key1Down]) {
        this->FirstPlayer.UpdateSpeed(getPongInit().RacketSpeed);
    } else {
        this->FirstPlayer.UpdateSpeed(0);
    }
    if (key[Key::Key2Up]) {
        this->SecondPlayer.UpdateSpeed(-getPongInit().RacketSpeed);
    } else if (key[Key::Key2Down]) {
        this->SecondPlayer.UpdateSpeed(getPongInit().RacketSpeed);
    } else {
        this->SecondPlayer.UpdateSpeed(0);
    }
    this->FirstPlayer.Update(this->dTime / 4);
    this->SecondPlayer.Update(this->dTime / 4);
    this->getBall().Update(this->dTime / 4, this->FirstPlayer.getPosition(), this->SecondPlayer.getPosition(),
            this->FirstPlayer.getSpeed(), this->SecondPlayer.getSpeed(), getPongInit());
    UpdateInscription(2, 45);
}


bool            Multiplayer::Events2(bool continues) {
    SDL_Event   event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT :
                setIfRunning(false);
                setIfExit(true);
                this->key[Key::KeyEsc] = false;
                break;
            case SDL_KEYDOWN : {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE : {
                        this->key[Key::KeyEsc] = false;
                        setIfRunning(false);
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN : {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    int xMouse = event.button.x, yMouse = event.button.y;
                    if (this->XContinue && getObjectPlayMenu()[1].ifPositionObject(xMouse, yMouse) && continues) {
                        MouseButtonDown(1);
                    } else if (getObjectPlayMenu()[2].ifPositionObject(xMouse, yMouse)) {
                        MouseButtonDown(2);
                    } else if (getObjectPlayMenu()[3].ifPositionObject(xMouse, yMouse)) {
                        MouseButtonDown(3);
                    }
                }
                break;
            }
            case SDL_MOUSEMOTION : {
                int xMouse, yMouse;
                SDL_GetMouseState(&xMouse, &yMouse);
                if (this->XContinue && getObjectPlayMenu()[1].ifPositionObject(xMouse, yMouse)) {
                    if (this->InducedInscription != 0) {
                        UpdateInscriptionPlayMenu(this->InducedInscription, true);
                    }
                    this->InducedInscription = 1;
                    UpdateInscriptionPlayMenu(this->InducedInscription, false);
                } else if (getObjectPlayMenu()[2].ifPositionObject(xMouse, yMouse)) {
                    if (this->InducedInscription != 0) {
                        UpdateInscriptionPlayMenu(this->InducedInscription, true);
                    }
                    this->InducedInscription = 2;
                    UpdateInscriptionPlayMenu(this->InducedInscription, false);
                } else if (getObjectPlayMenu()[3].ifPositionObject(xMouse, yMouse)) {
                    if (this->InducedInscription != 0) {
                        UpdateInscriptionPlayMenu(this->InducedInscription, true);
                    }
                    this->InducedInscription = 3;
                    UpdateInscriptionPlayMenu(this->InducedInscription, false);
                } else {
                    if (this->InducedInscription)
                        UpdateInscriptionPlayMenu(this->InducedInscription, true);
                    this->InducedInscription = 0;
                }
                break ;
            }
            default:
                break;
        }
    }
    return true ;
}

void            Multiplayer::MouseButtonDown(int i) {
    if (i == 1) {
        this->key[Key::KeyEsc] = false;
    } else if (i == 2) {
        getBall().setScoreFirst(0);
        getBall().setScoreSecond(0);
        getBall().Init(30, 30, Vect(WINDOW_WIDTH * 5 / 2 - (30 / 2), WINDOW_HEIGHT * 3 / 2 - (30 / 2)), Vect(getPongInit().MaxBallSpeed_x, 0));
        this->FirstPlayer.Init(RACKET_HEIGHT, RACKET_WIDTH, Vect(15, WINDOW_HEIGHT * 3 / 2 - (RACKET_HEIGHT / 2)), Vect(0, 0));
        this->SecondPlayer.Init(RACKET_HEIGHT, RACKET_WIDTH, Vect(WINDOW_WIDTH * 5 - 15 - RACKET_WIDTH, WINDOW_HEIGHT * 3 / 2 - (RACKET_HEIGHT / 2)), Vect(0, 0));
        this->key[Key::KeyEsc] = false;
    } else if (i == 3) {
        this->key[Key::KeyEsc] = false;
        setIfRunning(false);
    }
}

void            Multiplayer::Renderer() {
    if (this->key[Key::KeyPous])
        return ;
    SDL_RenderClear(getRenderer());
    getBackground().Draw(getRenderer());
    this->FirstPlayer.Draw(getRenderer());
    this->SecondPlayer.Draw(getRenderer());
    this->getBall().Draw(getRenderer());
    DrawAllText();
    SDL_RenderPresent(getRenderer());
    this->stopTime = std::chrono::high_resolution_clock::now();
    this->dTime = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
}

bool            Multiplayer::LoadAllText(int size) {
    int i = 1, x = WINDOW_WIDTH * 5 / 25, y = 10;
    for (const string &s : getStringText()) {
        if (i == 1)
            getObjectText()[i].loadObjectTextPlay(getRenderer(), s, size);
        if (i == 2)
            getObjectText()[i].loadObjectTextPlay(getRenderer(), this->_Ball.getStringScoreFirst() + s, size);
        if (i == 3)
            getObjectText()[i].loadObjectTextPlay(getRenderer(), this->_Ball.getStringScoreSecond() + s, size);
        int iW, iH;
        SDL_QueryTexture(getObjectText()[i].getObject(), nullptr, nullptr, &iW, &iH);
        if (i == 1)
            getObjectText()[i].Init(iH, iW, {(x - (iW / 2)), y});
        if (i == 2)
            getObjectText()[i].Init(iH, iW, {(x * 6 + 65 - (iW / 2)), y});
        if (i == 3)
            getObjectText()[i].Init(iH, iW, {(x * 18 - 50 - (iW / 2)), y});
        i++;
    }
    return true;
}

bool            Multiplayer::LoadWinner(int size, bool win) {
    int x = WINDOW_WIDTH * 5 / 2, y = WINDOW_HEIGHT * 3 / 10, i = 1;
    if (win)
        getObjectWinner()[i].loadObjectTextSet3(getRenderer(), getWinner()[0], size);
    if (!win)
        getObjectWinner()[i].loadObjectTextSet3(getRenderer(), getWinner()[1], size);
    int iW, iH;
    SDL_QueryTexture(getObjectWinner()[i].getObject(), nullptr, nullptr, &iW, &iH);
    getObjectWinner()[i].Init(iH, iW, {(x - (iW / 2)), y * 2});
    return true;
}

bool            Multiplayer::LoadPlayMenu(int size, bool ifContinue) {
    int x = WINDOW_WIDTH * 5 / 2, y = WINDOW_HEIGHT * 3 / 10, i = 1;
    for (const string &s : getPlayMenu()) {
        if (i == 1 && ifContinue)
            getObjectPlayMenu()[i].loadObjectText(getRenderer(), s, size);
        if (i == 2)
            getObjectPlayMenu()[i].loadObjectText(getRenderer(), s, size);
        if (i == 3)
            getObjectPlayMenu()[i].loadObjectText(getRenderer(), s, size);
        int iW, iH;
        SDL_QueryTexture(getObjectPlayMenu()[i].getObject(), nullptr, nullptr, &iW, &iH);
        if (i == 1 && ifContinue)
            getObjectPlayMenu()[i].Init(iH, iW, {(x - (iW / 2)), y * (i + 3)});
        if (i == 2)
            getObjectPlayMenu()[i].Init(iH, iW, {(x - (iW / 2)), y * (i + 3)});
        if (i == 3)
            getObjectPlayMenu()[i].Init(iH, iW, {(x - (iW / 2)), y * (i + 3)});
        i++;
    }
    return true;
}

void            Multiplayer::UpdateInscriptionPlayMenu(int ind, bool update) {
    int x = WINDOW_WIDTH * 5 / 2, y = WINDOW_HEIGHT * 3 / 10;
    if (update) {
        getObjectPlayMenu()[ind].Update(getRenderer(), getPlayMenu()[ind - 1], 45);
        int iW, iH;
        SDL_QueryTexture(getObjectPlayMenu()[ind].getObject(), nullptr, nullptr, &iW, &iH);
        getObjectPlayMenu()[ind].Init(iH, iW, {(x - (iW / 2)), y * (ind + 3)});
    } else {
        getObjectPlayMenu()[ind].Update(getRenderer(), getPlayMenu()[3] + getPlayMenu()[ind - 1] + getPlayMenu()[4], 45);
        int iW, iH;
        SDL_QueryTexture(getObjectPlayMenu()[ind].getObject(), nullptr, nullptr, &iW, &iH);
        getObjectPlayMenu()[ind].Init(iH, iW, {(x - (iW / 2)), y * (ind + 3)});
    }
}

void            Multiplayer::DrawWinner() {
    for (auto& m : getObjectWinner()) {
        m.second.Draw(getRenderer());
    }
}


void            Multiplayer::DrawPlayMenu() {
    int i = 1;
    for (auto& m : getObjectPlayMenu()) {
        if ((i == 1 && this->XContinue) || (i != 1))
            m.second.Draw(getRenderer());
        i++;
    }
}


void            Multiplayer::Renderer2() {
    SDL_RenderClear(getRenderer());
    getBackground().Draw(getRenderer());
    DrawAllText();
    if (getBall().getScoreFirst() == getPongInit().ScoreMax
        || getBall().getScoreSecond() == getPongInit().ScoreMax) {
        bool win = getBall().getScoreSecond() != getPongInit().ScoreMax;
        LoadWinner(35, win);
        DrawWinner();
    }
    DrawPlayMenu();
    SDL_RenderPresent(getRenderer());
}

void            Multiplayer::UpdateInscription(int ind1, int size) {
    getObjectText()[ind1].CleanObject();
    getObjectText()[ind1 + 1].CleanObject();
    getObjectText()[ind1].loadObjectTextPlay(getRenderer(),
                this->getBall().getStringScoreFirst() + getStringText()[ind1 - 1], size);
    getObjectText()[ind1 + 1].loadObjectTextPlay(getRenderer(),
                this->getBall().getStringScoreSecond() + getStringText()[ind1], size);
}
