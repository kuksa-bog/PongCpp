#ifndef PLAY_HPP
# define PLAY_HPP

#include "View.hpp"


class Multiplayer : public View {
public:
    explicit Multiplayer(struct PongInit& pongInit) : dTime(16), InducedInscription(0), XContinue(false) {
        setPongInit(pongInit);
        cout << "Multiplayer created...." << endl; };
    ~Multiplayer() override { cout << "Multiplayer destroyed...." << endl; };

    bool            Running() override ;

    bool            LoadAllText(int size) override ;

    bool            LoadPlayMenu(int size, bool ifContinue);

    bool            LoadWinner(int size, bool win);

    void            UpdateInscription(int ind1, int size);

    void            UpdateInscriptionPlayMenu(int ind, bool update);

    void            setWinner(const vector<string> &v) { this->Winner = v; };

    void            setPlayMenu(const vector<string> &v) { this->PlayMenu = v; };

    Ball&           getBall() { return this->Ball; };

    bool                key[6] = {};
    Racket              FirstPlayer;
    std::chrono::high_resolution_clock::time_point   stopTime;
    std::chrono::high_resolution_clock::time_point   startTime;
    int                                              dTime;

private:
    virtual void    MouseButtonDown(int ind);

    void            DrawWinner();

    void            DrawPlayMenu();

    void            Init() override ;

    bool            Events() override;

    bool            Events2(bool continues);

    void            Update() override;

    void            Renderer() override;

    void            Renderer2();

    void            Clean() override {};

    vector<string>& getWinner() { return this->Winner; };

    vector<string>& getPlayMenu() { return this->PlayMenu; };

    map<int, Text>& getObjectWinner() { return this->ObjectWinner; };

    map<int, Text>& getObjectPlayMenu() { return this->ObjectPlayMenu; };

private:
    int                 InducedInscription;
    bool                XContinue;
    Racket              SecondPlayer;
    Ball                Ball;
    map<int, Text>      ObjectWinner;
    map<int, Text>      ObjectPlayMenu;
    vector<string>      Winner;
    vector<string>      PlayMenu;
};







class SinglePlayer : public Multiplayer {
public:
    explicit SinglePlayer(struct PongInit& pongInit) : Multiplayer(pongInit) {
        cout << "SinglePlayer created...." << endl; };
    ~SinglePlayer() override { cout << "SinglePlayer destroyed...." << endl; };

    Bot&                getBot() { return this->itIsBot; };

private:
    void            MouseButtonDown(int i) override ;

    bool            Events() override ;

    void            Renderer() override ;

    void            Init() override ;

    void            Update() override ;

    Bot                 itIsBot;

};







class Tutorial : public View {
public:
    explicit Tutorial(struct PongInit& pongInit) {
        setPongInit(pongInit);
        cout << "Tutorial created...." << endl; };
    ~Tutorial() override { cout << "Tutorial destroyed...." << endl; };

    bool            LoadAllText(int size) override ;

    void            InitText(int ind) override ;

    void            UpdateInscription(int ind, bool update);

private:
    void            Init() override;

    bool            Events() override;

    void            Update() override;

    void            Renderer() override;

    int                     InducedInscription{};
    uint32_t                CaseNumber{};
};






class Settings : public View {
public:
    explicit Settings(struct PongInit& pongInit) : MaxScroll(300), MinScroll(0), ScrollMove(30), ScrollNum(300) {
        setPongInit(pongInit);
        cout << "Settings created...." << endl; };
    ~Settings() override { cout << "Settings destroyed...." << endl; };

    bool                LoadAllText(int size) override ;

    void                InitText(int ind) override ;



    bool                LoadAllBalls();

    void                InitBalls(int ind);

    void                DrawAllBalls();

    map<int, Texture>&  getObjectBalls() { return this->ObjectBalls; };



    map<int, Texture>&  getMapBackground() { return this->MapBackground; };

    map<int, RectPong>& getRectBackground() { return this->RectBackground; };

    bool                LoadMapBackground();

    void                InitMapBackground(int ind);

    void                DrawMapBackground();



    void                InitAllLeftRackets(int ind);

    bool                LoadAllLeftRackets();

    void                DrawAllLeftRackets();

    map<int, Texture>&  getObjectRacketLeft() { return this->ObjectRacketLeft; };



    void                InitAllRightRackets(int ind);

    bool                LoadAllRightRackets();

    void                DrawAllRightRackets();

    map<int, Texture>&  getObjectRacketRight() { return this->ObjectRacketRight; };




    void                ScrollUpdate(bool scroll);




    static bool         CaseNumber_static(int num1, int num2) { return num1 != num2; };




    void                UpdateInscription(int ind, int update);

    void                UpdatePongInit(int update, int toNumString, int& PongCase);

    void                UpdatePongInitScore(int update, int toNumString, int& PongCase);

    void                UpdatePongInitBackground(int update, int& PongCase);

    void                UpdateMouseMotion(int update);


private:
    void                Init() override;

    bool                Events() override;

    void                Update() override;

    void                Renderer() override;

    int                              InducedInscription{};
    map<int, RectPong>               RectBackground;
    map<int, Texture>                MapBackground;
    map<int, Texture>                ObjectBalls;
    map<int, Texture>                ObjectRacketLeft;
    map<int, Texture>                ObjectRacketRight;
    int                              CaseNumber{};
    int                              MaxScroll;
    int                              MinScroll;
    int                              ScrollMove;
    int                              ScrollNum;
    int                              xMouseset{}, yMouseset{};
};

#endif
