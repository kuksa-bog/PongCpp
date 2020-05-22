#include "../include/Controller.hpp"

void    Controller::Menu() {
    bool running = true;
    SDL_Event event;
    string path = "DejaVuSansMono.ttf";
    SDL_Texture *First_player = RenderText("Single player", path, w, 1);
    SDL_Texture *Second_player = RenderText("Multiplayer", path, w, 1);
    SDL_Texture *Exit = RenderText("Exit", path, w, 1);

    while (running) {
        SDL_WaitEvent(&event);
            switch (event.type) {
                case SDL_QUIT : {
                    running = false;
                    break ;
                }
                case SDL_KEYDOWN : {
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE : {
                            running = false;
                            break;
                        }
                    }
                    break;
                }
                case SDL_MOUSEBUTTONDOWN : {
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        int x = event.button.x, y = event.button.y;
                        if (x >= (WINDOW_WIDTH / 2) - 135 && x <= (WINDOW_WIDTH / 2) + 135
                            && y >= (WINDOW_HEIGHT / 4) - 15 && y <= (WINDOW_HEIGHT / 4) + 22) {
                            View Bot1;
                            Bot1.GameVsBot(w);
                            SDL_SetRenderDrawColor( w.renderer, 0x0, 0x0, 0x0, 0xFF );
                            w.color_txt = {255, 255, 255, 255};
                            First_player = RenderText("Single player", path, w, 1);
                            Second_player = RenderText("Multiplayer", path, w, 1);
                            Exit = RenderText("Exit", path, w, 1);
                        } else if (x >= (WINDOW_WIDTH / 2) - 115 && x <= (WINDOW_WIDTH / 2) + 115
                            && y >= (WINDOW_HEIGHT / 3) - 15 && y <= (WINDOW_HEIGHT / 3) + 22) {
                            View Multiplayer;
                            Multiplayer.GameMultiplayer(w);
                            SDL_SetRenderDrawColor( w.renderer, 0x0, 0x0, 0x0, 0xFF );
                            w.color_txt = {255, 255, 255, 255};
                            First_player = RenderText("Single player", path, w, 1);
                            Second_player = RenderText("Multiplayer", path, w, 1);
                            Exit = RenderText("Exit", path, w, 1);
                        } else if (x >= (WINDOW_WIDTH / 2) - 40 && x <= (WINDOW_WIDTH / 2) + 40
                                   && y >= static_cast<int>(WINDOW_HEIGHT / 2.4f) - 15
                                   && y <= static_cast<int>(WINDOW_HEIGHT / 2.4f) + 22) {
                            close(w);
                            exit(1);
                        }
                    }
                    break;
                }
                case SDL_MOUSEMOTION : {
                    int xMouse, yMouse;
                    SDL_GetMouseState(&xMouse, &yMouse);
                    if (xMouse >= (WINDOW_WIDTH / 2) - 135 && xMouse <= (WINDOW_WIDTH / 2) + 135
                        && yMouse >= (WINDOW_HEIGHT / 4) - 15 && yMouse <= (WINDOW_HEIGHT / 4) + 22) {
                        w.color_txt = {255, 255, 100, 255};
                        SDL_RenderClear(w.renderer);
                        First_player = RenderText("Single player", path, w, 1);
                    } else if (xMouse >= (WINDOW_WIDTH / 2) - 115 && xMouse <= (WINDOW_WIDTH / 2) + 115
                               && yMouse >= (WINDOW_HEIGHT / 3) - 15 && yMouse <= (WINDOW_HEIGHT / 3) + 22) {
                        w.color_txt = {255, 255, 100, 255};
                        SDL_RenderClear(w.renderer);
                        Second_player = RenderText("Multiplayer", path, w, 1);
                    } else if (xMouse >= (WINDOW_WIDTH / 2) - 40 && xMouse <= (WINDOW_WIDTH / 2) + 40
                               && yMouse >= static_cast<int>(WINDOW_HEIGHT / 2.4f) - 15 && yMouse <= static_cast<int>(WINDOW_HEIGHT / 2.4f) + 22) {
                        w.color_txt = {255, 255, 100, 255};
                        SDL_RenderClear(w.renderer);
                        Exit = RenderText("Exit", path, w, 1);
                    } else {
                        w.color_txt = {255, 255, 255, 255};
                        First_player = RenderText("Single player", path, w, 1);
                        Second_player = RenderText("Multiplayer", path, w, 1);
                        Exit = RenderText("Exit", path, w, 1);
                    }
                    break ;
                }
            }
        SDL_RenderClear(w.renderer);
        PutText(w, WINDOW_HEIGHT / (4), First_player, 1);
        PutText(w, WINDOW_HEIGHT / (3), Second_player, 1);
        PutText(w, static_cast<int>(WINDOW_HEIGHT / 2.4f), Exit, 1);
        SDL_RenderPresent(w.renderer);
    }
    SDL_DestroyTexture(First_player);
    SDL_DestroyTexture(Second_player);
    SDL_DestroyTexture(Exit);

}