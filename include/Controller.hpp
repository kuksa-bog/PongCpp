#ifndef CONTROLLER_HPP
# define CONTROLLER_HPP

#include "View.hpp"

class Controller {
public:
    Controller(wind &w) : w(w) {}
    void	Menu();
    wind w;
};

#endif
