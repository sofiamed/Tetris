#ifndef include_Fenetre
#define include_Fenetre

#include "defs.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace Graphique {
    class Fenetre {
        public:
            Fenetre(std::string titre, int w=640, int h=480, int x=SDL_WINDOWPOS_UNDEFINED, int y=SDL_WINDOWPOS_UNDEFINED, bool main_window=true);
            ~Fenetre();



        protected:
            static unsigned nb_instances;
            static bool is_sdl_init;

            bool main_window;
            SDL_Window* pWindow;
            std::string titre;


        private:

    };

}

#endif // Class Fenetre
