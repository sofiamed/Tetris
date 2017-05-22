#include "Fenetre.hpp"

namespace Graphique {

    unsigned Fenetre::nb_instances = 0;
    bool Fenetre::is_sdl_init = false;

    Fenetre::Fenetre(std::string titre, int w, int h, int x, int y, bool main_window) : main_window(main_window), pWindow(nullptr), titre(titre) {
        if(!is_sdl_init) {
            SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
            is_sdl_init = true;
            ++nb_instances;
            std::cout << "SDL_Init(...);" << std::endl;
        }

        pWindow = SDL_CreateWindow(titre.c_str(), x, y, w, h, SDL_WINDOW_SHOWN);
        SDL_Delay(1500);

    }

    Fenetre::~Fenetre() {

        if(pWindow)
            SDL_DestroyWindow(pWindow);




        if(main_window && --nb_instances == 0) {
            SDL_Quit();
            std::cout << "SDL_Quit();" << std::endl;
        }
    }

}
