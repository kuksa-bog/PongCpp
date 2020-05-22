#include "../include/Controller.hpp"

int main() {
    wind w;
    if( !init(w) ) {
        cout << "Failed to initialize!" << endl;
    } else {
        if( !loadMedia(w) ) {
            cout << "Failed to load media!" << endl;
        }
        Controller controller(w);
        controller.Menu();
    }
    close(w);
    return 0;
}

