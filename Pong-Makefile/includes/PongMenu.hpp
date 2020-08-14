#ifndef PONGMENU_HPP
# define PONGMENU_HPP

#include "Play.hpp"

class PongMenu : public View {
public:
    PongMenu() : InducedInscription(0) { cout << "PongMenu created...." << endl; };
    ~PongMenu() override { cout << "PongMenu destroyed...." << endl; };

    void            UpdateInscription(int ind, bool update);

    bool            LoadAllText(int size) override ;

    void            InitText(int ind) override ;

private:
    void            Init() override ;

    bool            Events() override ;

    void            Update() override ;

    void            Renderer() override ;

    void            Clean() override ;

    int                     InducedInscription;
    uint32_t                CaseNumber{};
};

#endif
