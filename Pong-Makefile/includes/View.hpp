#ifndef VIEW_HPP
# define VIEW_HPP

#include "Object.hpp"

class View {
public:
    View() { cout << "Play created...." << endl; };
    virtual ~View() { cout << "Play destroyed...." << endl; };



    virtual bool            Running();

    void                    setIfRunning(bool run) { this->IfRunning = run; };

    bool                    ifContinue() { return this->IfRunning; };



    virtual bool            LoadAllText(int size);

    virtual void            InitText(int ind);

    virtual void            DrawAllText();



    Texture&                getBackground() { return this->Background; };

    map<int, Text>&         getObjectText() { return this->ObjectText; };

    vector<string>&         getStringText() { return this->StringText; };

    void                    setStringText(const vector<string>  &vect) { this->StringText = vect; };



    void                    updateIfExit(PongInit& pongInit) { pongInit.ifExit = getIfExit(); };

    void                    updatePongInit(PongInit& pongInit);

    void                    setPongInit(PongInit& pongInit);

    void                    setIfExit(bool exit) { this->_PongInit.ifExit = exit; };

    void                    setWindow(SDL_Window *window) { this->_PongInit.window = window; };

    void                    setRenderer(SDL_Renderer *renderer) { this->_PongInit.renderer = renderer; };

    PongInit&               getPongInit() { return this->_PongInit; };

    bool                    getIfExit() { return this->_PongInit.ifExit; };

    SDL_Window*             getWindow() { return this->_PongInit.window; };

    SDL_Renderer*           getRenderer() { return  this->_PongInit.renderer; };

private:
    virtual void            Init() {};

    virtual bool            Events() { return true; };

    virtual void            Update() {};

    virtual void            Renderer() {};

    virtual void            Clean() {};

    PongInit                _PongInit;
    map<int, Text>          ObjectText;
    Texture                 Background;
    vector<string>          StringText;
    bool                    IfRunning{};
};

#endif
