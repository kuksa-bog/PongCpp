#include "Play.hpp"

void            Tutorial::Init() {
    setIfRunning(true);
    setStringText({"Tutorial",
                   "Left racket control: up -> [W], down -> [S]",
                   "Right racket control: up -> [UP], down -> [DOWN]",
                   "Pause -> [SPACE]",
                   "Predict the movement of the ball, move the racket",
                   "to bounce the ball back.",
                   "Think of the best way of hitting the ball back",
                   "so it will be more difficult",
                   "for your opponent to predict the movement.", "Exit to menu", "* ", " *"});
    if (getBackground().loadObject(getRenderer(), "../resources/images/Backgrounds/Background1.png")) {
        getBackground().Init(WINDOW_HEIGHT * 3, WINDOW_WIDTH * 5, Vect(0, 0));
        if (!LoadAllText(35)) {
            cout << "Error:PongMenu::Init: load All Text" << SDL_GetError() << endl;
            setIfRunning(false);
        }
    } else {
        cout << "Error:PongMenu::Init: load Background" << SDL_GetError() << endl;
        setIfRunning(false);
    }
}


bool            Tutorial::Events() {
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
        case SDL_MOUSEBUTTONDOWN : {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                int xMouse = event.button.x, yMouse = event.button.y;
                if (getObjectText()[10].ifPositionObject(xMouse, yMouse)) {
                    setIfRunning(false);
                }
            }
            break;
        }
        case SDL_MOUSEMOTION : {
            int xMouse, yMouse;
            SDL_GetMouseState(&xMouse, &yMouse);
            if (getObjectText()[10].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 1) ? 1 : 2;                            // if case Single Plater
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

void            Tutorial::Update() {
    if (this->CaseNumber == 1) {
        if (this->InducedInscription != 0) {
            UpdateInscription(this->InducedInscription, true);
        }
        this->InducedInscription = 10;
        UpdateInscription(this->InducedInscription, false);
    } else if (this->InducedInscription != 0 && this->CaseNumber != 2) {
        UpdateInscription(this->InducedInscription, true);
        this->InducedInscription = 0;
    }
}

void            Tutorial::Renderer() {
    SDL_RenderClear(getRenderer());
    getBackground().Draw(getRenderer());
    DrawAllText();
    SDL_RenderPresent(getRenderer());
}


void            Tutorial::InitText(int ind) {
    int x = WINDOW_WIDTH * 5 / 2, y = WINDOW_HEIGHT * 3 / 15;
    int iW, iH;
    SDL_QueryTexture(getObjectText()[ind].getObject(), nullptr, nullptr, &iW, &iH);
    if (ind < 10)
        getObjectText()[ind].Init(iH, iW, {(x - (iW / 2)), (y * ind - (iH / 2))});
    else
        getObjectText()[ind].Init(iH, iW, {(x - (iW / 2)), (y * (ind + 1) - (iH / 2))});
}

void            Tutorial::UpdateInscription(int ind, bool update) {
    if (update) {
        getObjectText()[ind].Update(getRenderer(), getStringText()[ind - 1], 35);
        InitText(ind);
    } else {
        getObjectText()[ind].Update(getRenderer(), getStringText()[10] + getStringText()[ind - 1] + getStringText()[11], 35);
        InitText(ind);
    }
}

bool            Tutorial::LoadAllText(int size) {
    int i = 1;
    for (const string &s : getStringText()) {
        if (i <= 10) {
            getObjectText()[i].loadObjectText(getRenderer(), s, size);
            InitText(i);
        }
        i++;
    }
    return true;
}

