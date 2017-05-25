#ifndef include_Fenetre
#define include_Fenetre

#include "Blocs.hpp"
#include "defs.hpp"

namespace Graphique {


    class Fenetre {
        public:
            Fenetre(std::string titre, int w=640, int h=480, int x=SDL_WINDOWPOS_UNDEFINED, int y=SDL_WINDOWPOS_UNDEFINED, bool main_window=true);
            ~Fenetre();


            void blitBloc(Blocs::Brique& b, int x=0, int y=0, SDL_Rect* crop_rect=NULL);
            void blitBlocExact(Blocs::Brique& b, int id_x=0, int id_y=0, SDL_Rect* crop_rect=NULL);
            void blitBloc(Blocs::Brique& b, SDL_Rect* crop_rect=NULL);
            inline void clear(bool changerCouleur=false, u8 r=0, u8 g=0, u8 b=0, u8 a=255) { if(changerCouleur) SDL_SetRenderDrawColor(pRenderer, r,g,b,a); SDL_RenderClear(pRenderer);}
            inline void pause(u32 ms) const { SDL_Delay(ms); }
            inline void update() { SDL_RenderPresent(pRenderer); }
            void loop(Blocs::ListeBriques&,  void (*boucle)(Blocs::ListeBriques&)=nullptr );


        protected:
            static unsigned nb_instances;
            static bool is_sdl_init;

            bool main_window;
            SDL_Window* pWindow;
            std::string titre;

            SDL_Renderer *pRenderer;
            std::vector<SDL_Texture*> pTexture_blocs;


        private:

            int width,height,posX,posY;

    };

}

#endif // Class Fenetre
