#include "../include/View.hpp"

void    View::GameMultiplayer(wind &w) const {
    string path = "DejaVuSansMono.ttf";
    WidthAndHeightOfObjects(w);
    Ball ball(Vect((WINDOW_WIDTH / 2.0f),(WINDOW_HEIGHT / 2.0f)), Vect(BALL_SPEED, 0.0f));
    Racket RacketOne(Vect(50.0f, (WINDOW_HEIGHT / 2.0f) - (w.racket_width / 2.0f)), Vect(0.0f, 0.0f));
    Racket RacketTwo(Vect(WINDOW_WIDTH - 50.0f, (WINDOW_HEIGHT / 2.0f) - (w.racket_height / 2.0f)), Vect(0.0f, 0.0f));

    SDL_Color color_txt2 = w.color_txt;
    w.color_txt = {0, 0, 0, 255};
    SDL_Texture *esc = RenderText("esc", path, w, 2);
    w.color_txt = color_txt2;
    bool key[4] = {};
    SDL_Event event;
    float dt = 0.0f;
    while (true) {
        auto startTime = std::chrono::high_resolution_clock::now();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT : {
                    close(w);
                    exit(1);
                }
                case SDL_KEYDOWN : {
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE : {
                            return;
                        }
                        case SDLK_w : {
                        key[Key::Key1Up] = true;
                        break ;
                        }
                        case SDLK_s : {
                            key[Key::Key1Down] = true;
                            break ;
                        }
                        case SDLK_UP : {
                            key[Key::Key2Up] = true;
                            break ;
                        }
                        case SDLK_DOWN : {
                            key[Key::Key2Down] = true;
                            break ;
                        }
                    }
                    break;
                }
                case SDL_KEYUP : {
                    switch (event.key.keysym.sym) {
                        case SDLK_w : {
                            key[Key::Key1Up] = false;
                            break ;
                        }
                        case SDLK_s : {
                            key[Key::Key1Down] = false;
                            break ;
                        }
                        case SDLK_UP : {
                            key[Key::Key2Up] = false;
                            break ;
                        }
                        case SDLK_DOWN : {
                            key[Key::Key2Down] = false;
                            break ;
                        }
                    }
                    break;
                }
            }
        }
        SDL_SetRenderDrawColor(w.renderer, 0x30, 0x30, 0x30, 0xFF);
        SDL_RenderClear(w.renderer);
        RenderBackground(w);
        PutText(w, 10, esc, 2);
        DrawsTheNet(w.renderer);
        SDL_Color color_txt = w.color_txt;
        w.color_txt = {255, 100, 100, 255};
        SDL_Texture *ScoreOneText = RenderText(to_string(ball.ScoreOne) + "/8", path, w, 1);
        SDL_Texture *ScoreTwoText = RenderText(to_string(ball.ScoreTwo) + "/8", path, w, 1);
        ball.PutText(w.renderer, 30, ScoreOneText, 1);
        ball.PutText(w.renderer, 30, ScoreTwoText, 0);
        w.color_txt = color_txt;
        if (key[Key::Key1Up]) {
            RacketOne.speed.y = -RACKET_SPEED;
        } else if (key[Key::Key1Down]) {
            RacketOne.speed.y = RACKET_SPEED;
        } else {
            RacketOne.speed.y = 0.0f;
        }
        if (key[Key::Key2Up]) {
            RacketTwo.speed.y = -RACKET_SPEED;
        } else if (key[Key::Key2Down]) {
            RacketTwo.speed.y = RACKET_SPEED;
        } else {
            RacketTwo.speed.y = 0.0f;
        }
        RacketOne.Update(dt, w.racket_height);
        RacketTwo.Update(dt, w.racket_height);
        RacketOne.Draw(w.renderer, w.image_racket1);
        RacketTwo.Draw(w.renderer, w.image_racket2);
        if (IfTouchRacket(ball, RacketOne, w)) {
            Mix_PlayChannel(-1, w.racketHitSound, 0);
            ball.speed.x = -ball.speed.x;
            ball.speed.y = ball.speed.y + RacketOne.speed.y / 4;
        } else if (IfTouchRacket(ball, RacketTwo, w)) {
            Mix_PlayChannel(-1, w.racketHitSound, 0);
            ball.speed.x = -ball.speed.x;
            ball.speed.y = ball.speed.y + RacketTwo.speed.y / 4;
        }
        ball.IfTouchWall(w.ball_height, w.ball_width, w.wallHitSound);
        if (ball.ScoreTwo == 8 || ball.ScoreOne == 8) {
            w.Win = (ball.ScoreTwo == 8) ? 2 : 1;
            Winner(w, ball, RacketOne, RacketTwo);
            return ;
        }
        ball.Update(dt);
        ball.Draw(w.renderer, w.image_bll);
        SDL_RenderPresent(w.renderer);
        auto stopTime = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
    }
}

void    View::GameVsBot(wind &w) const {
    string path = "DejaVuSansMono.ttf";
    WidthAndHeightOfObjects(w);
    Ball ball(Vect((WINDOW_WIDTH / 2.0f),(WINDOW_HEIGHT / 2.0f)), Vect(BALL_SPEED, 0.0f));
    Racket RacketOne(Vect(50.0f, (WINDOW_HEIGHT / 2.0f) - (w.racket_width / 2.0f)), Vect(0.0f, 0.0f));
    Bot RacketBot(Vect(WINDOW_WIDTH - 50.0f, (WINDOW_HEIGHT / 2.0f) - (w.racket_height / 2.0f)), Vect(0.0f, 0.0f), true, 1);

    SDL_Color color_txt2 = w.color_txt;
    w.color_txt = {0, 0, 0, 255};
    SDL_Texture *esc = RenderText("esc", path, w, 2);
    w.color_txt = color_txt2;

    bool key[4] = {};
    SDL_Event event;
    float dt = 0.0f;
    RacketBot.SearchPlaceHard(ball, w, 16.5);
    while (true) {
        auto startTime = std::chrono::high_resolution_clock::now();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT : {
                    close(w);
                    exit(1);
                }
                case SDL_KEYDOWN : {
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE : {
                            return;
                        }
                        case SDLK_w : {
                            key[Key::Key1Up] = true;
                            break ;
                        }
                        case SDLK_s : {
                            key[Key::Key1Down] = true;
                            break ;
                        }
                    }
                    break;
                }
                case SDL_KEYUP : {
                    switch (event.key.keysym.sym) {
                        case SDLK_w : {
                            key[Key::Key1Up] = false;
                            break ;
                        }
                        case SDLK_s : {
                            key[Key::Key1Down] = false;
                            break ;
                        }
                    }
                    break;
                }
            }
        }
        SDL_SetRenderDrawColor(w.renderer, 0x30, 0x30, 0x30, 0xFF);
        SDL_RenderClear(w.renderer);
        RenderBackground(w);
        PutText(w, 10, esc, 2);
        DrawsTheNet(w.renderer);
        SDL_Color color_txt = w.color_txt;
        w.color_txt = {255, 100, 100, 255};
        SDL_Texture *ScoreOneText = RenderText(to_string(ball.ScoreOne) + "/8", path, w, 1);
        SDL_Texture *ScoreTwoText = RenderText(to_string(ball.ScoreTwo) + "/8", path, w, 1);
        ball.PutText(w.renderer, 30, ScoreOneText, 1);
        ball.PutText(w.renderer, 30, ScoreTwoText, 0);
        w.color_txt = color_txt;
        if (key[Key::Key1Up]) {
            RacketOne.speed.y = -RACKET_SPEED;
        } else if (key[Key::Key1Down]) {
            RacketOne.speed.y = RACKET_SPEED;
        } else {
            RacketOne.speed.y = 0.0f;
        }
        RacketOne.Update(dt, w.racket_height);
        RacketBot.Update(dt, w.racket_height);
        RacketOne.Draw(w.renderer, w.image_racket1);
        RacketBot.Draw(w.renderer, w.image_racket2);
        if (IfTouchRacket(ball, RacketOne, w)) {
            Mix_PlayChannel(-1, w.racketHitSound, 0);
            ball.speed.x = -ball.speed.x;
            ball.speed.y = ball.speed.y + RacketOne.speed.y / 4;
            RacketBot.SearchPlaceHard(ball, w, dt);
        } else if (IfTouchRacket(ball, RacketBot, w)) {
            Mix_PlayChannel(-1, w.racketHitSound, 0);
            ball.speed.x = -ball.speed.x;
            ball.speed.y = ball.speed.y + RacketBot.speed.y / 4;
        }
        if (ball.IfTouchWall(w.ball_height, w.ball_width, w.wallHitSound)) {
            RacketBot.SearchPlaceHard(ball, w, dt);
        }
        if (ball.ScoreTwo == 8 || ball.ScoreOne == 8) {
            w.Win = (ball.ScoreTwo == 8) ? 2 : 1;
            Winner(w, ball, RacketOne, RacketBot);
            return ;
        }
        ball.Update(dt);
        ball.Draw(w.renderer, w.image_bll);
        SDL_RenderPresent(w.renderer);
        auto stopTime = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
    }
//    if (ball.ScoreTwo == 8 || ball.ScoreOne == 8) {
//        w.Win = (ball.ScoreTwo == 8) ? 2 : 1;
//        Winner(w, ball, RacketOne, RacketBot);
//        return ;
//    }
}
