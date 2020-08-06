#include "../includes/PongMenu.hpp"

void            PongMenu::Init() {
    setIfRunning(true);
    setStringText({"Single player", "Multiplayer", "Tutorial", "Settings", "Exit", "v2.0", "* ", " *"});
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        setIfRunning(false);
    } else if ( TTF_Init() < 0 ) {
        cout << "SDL_ttf could not initialize! SDL Error: " << TTF_GetError() << endl;
        setIfRunning(false);
    } else if ( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) ) {
        cout << "SDL_image could not initialize! SDL Error: " << IMG_GetError() << endl;
        setIfRunning(false);
    } else {
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
            cout << "Warning: Linear texture filtering not enabled!" << endl;
        }
        setWindow(SDL_CreateWindow( "Pong-bkuksa", SDL_WINDOWPOS_UNDEFINED,
                                             0, WINDOW_WIDTH * 5, WINDOW_HEIGHT * 3, SDL_WINDOW_SHOWN ));
        if( getWindow() == nullptr ) {
            cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
            setIfRunning(false);
        } else {
            setRenderer(SDL_CreateRenderer( getWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC ));
            if ( getRenderer() == nullptr ) {
                cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
                setIfRunning(false);
            } else {
                if (getBackground().loadObject(getRenderer(), "resources/images/Backgrounds/Background1.png")) {
                    getBackground().Init(WINDOW_HEIGHT * 3, WINDOW_WIDTH * 5, Vect(0, 0));
                    if (!LoadAllText(45)) {
                        cout << "Error:PongMenu::Init: load All Text" << SDL_GetError() << endl;
                        setIfRunning(false);
                    }
                } else {
                    cout << "Error:PongMenu::Init: load Background" << SDL_GetError() << endl;
                    setIfRunning(false);
                }
            }
        }
    }
}

bool            PongMenu::Events() {
    SDL_Event   event;
    SDL_WaitEvent(&event);
    switch (event.type) {
        case SDL_QUIT :
            setIfRunning(false);
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
                if (getObjectText()[1].ifPositionObject(xMouse, yMouse)) {
                    SinglePlayer single(getPongInit());
                    setIfRunning(single.Running());
                    single.updateIfExit(getPongInit());
                    this->CaseNumber = 0;
                } else if (getObjectText()[2].ifPositionObject(xMouse, yMouse)) {
                    Multiplayer multi(getPongInit());
                    setIfRunning(multi.Running());
                    multi.updateIfExit(getPongInit());
                    this->CaseNumber = 0;
                } else if (getObjectText()[3].ifPositionObject(xMouse, yMouse)) {
                    Tutorial tutorial(getPongInit());
                    setIfRunning(tutorial.Running());
                    tutorial.updateIfExit(getPongInit());
                    this->CaseNumber = 0;
                } else if (getObjectText()[4].ifPositionObject(xMouse, yMouse)) {
                    Settings settings(getPongInit());
                    setIfRunning(settings.Running());
                    settings.updatePongInit(getPongInit());
                    this->CaseNumber = 0;
                } else if (getObjectText()[5].ifPositionObject(xMouse, yMouse)) {
                    setIfRunning(false);
                }
            }
            break;
        }
        case SDL_MOUSEMOTION : {
            int xMouse, yMouse;
            SDL_GetMouseState(&xMouse, &yMouse);
            if (getObjectText()[1].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 1) ? 1 : 6;                            // if case Single Plater
            } else if (getObjectText()[2].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 2) ? 2 : 6;                            // if case multiplayer
            } else if (getObjectText()[3].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 3) ? 3 : 6;                            // if case exit
            } else if (getObjectText()[4].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 4) ? 4 : 6;                            // if case exit
            } else if (getObjectText()[5].ifPositionObject(xMouse, yMouse)) {
                this->CaseNumber = (this->CaseNumber != 5) ? 5 : 6;                            // if case exit
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

void            PongMenu::Update() {
    if (this->CaseNumber == 1) {
        if (this->InducedInscription != 0) {
            UpdateInscription(this->InducedInscription, true);
        }
        this->InducedInscription = 1;
        UpdateInscription(this->InducedInscription, false);
    } else if (this->CaseNumber == 2) {
        if (this->InducedInscription != 0) {
            UpdateInscription(this->InducedInscription, true);
        }
        this->InducedInscription = 2;
        UpdateInscription(this->InducedInscription, false);
    } else if (this->CaseNumber == 3) {
        if (this->InducedInscription != 0) {
            UpdateInscription(this->InducedInscription, true);
        }
        this->InducedInscription = 3;
        UpdateInscription(this->InducedInscription, false);
    } else if (this->CaseNumber == 4) {
        if (this->InducedInscription != 0) {
            UpdateInscription(this->InducedInscription, true);
        }
        this->InducedInscription = 4;
        UpdateInscription(this->InducedInscription, false);
    } else if (this->CaseNumber == 5) {
        if (this->InducedInscription != 0) {
            UpdateInscription(this->InducedInscription, true);
        }
        this->InducedInscription = 5;
        UpdateInscription(this->InducedInscription, false);
    } else if (this->InducedInscription != 0 && this->CaseNumber != 6) {
        UpdateInscription(this->InducedInscription, true);
        this->InducedInscription = 0;
    }
}

void            PongMenu::Renderer() {
    SDL_RenderClear(getRenderer());
    getBackground().Draw(getRenderer());
    DrawAllText();
    SDL_RenderPresent(getRenderer());
}

void            PongMenu::Clean() {
    SDL_DestroyRenderer(getRenderer());
    SDL_DestroyWindow(getWindow());
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
    Mix_Quit();
    cout << "PongMenu cleaned...." << endl;
}


void            PongMenu::InitText(int ind) {
    int x = WINDOW_WIDTH * 5 / 2, y = WINDOW_HEIGHT * 3 / 10;
    int iW, iH;
    SDL_QueryTexture(getObjectText()[ind].getObject(), nullptr, nullptr, &iW, &iH);
    if (ind != 6)
        getObjectText()[ind].Init(iH, iW, {(x - (iW / 2)), (y * ind - (iH / 2))});
    else
        getObjectText()[ind].Init(iH, iW, {10, WINDOW_HEIGHT * 3 - 35});
}

void            PongMenu::UpdateInscription(int ind, bool update) {
    if (update) {
        getObjectText()[ind].Update(getRenderer(), getStringText()[ind - 1], 45);
        InitText(ind);
    } else {
        getObjectText()[ind].Update(getRenderer(), getStringText()[6] + getStringText()[ind - 1] + getStringText()[7], 45);
        InitText(ind);
    }
}

bool            PongMenu::LoadAllText(int size) {
    int i = 1;
    for (const string &s : getStringText()) {
        if (i <= 5) {
            getObjectText()[i].loadObjectText(getRenderer(), s, size);
            InitText(i);
        }
        if (i == 6) {
            getObjectText()[i].loadObjectText(getRenderer(), s, size / 2);
            InitText(i);
        }
        i++;
    }
    return true;
}
