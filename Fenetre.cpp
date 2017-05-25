#include "Fenetre.hpp"
#include "Blocs.hpp"

namespace Graphique {

    unsigned Fenetre::nb_instances = 0;
    bool Fenetre::is_sdl_init = false;

    Fenetre::Fenetre(std::string titre, int w, int h, int x, int y, bool main_window) : main_window(main_window), pWindow(nullptr), titre(titre), width(w), height(h), posX(x), posY(y) {
        if(!is_sdl_init) {
            SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
            is_sdl_init = true;
            ++nb_instances;



            pWindow   = SDL_CreateWindow(titre.c_str(), x, y, w, h, SDL_WINDOW_SHOWN);
            pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED);



            pTexture_blocs.resize(Blocs::Types::nb_types);
            for(unsigned i=0; i!=Blocs::Types::nb_types; ++i) {
                Blocs::Types::sprites[i] = IMG_Load((Blocs::Types::basedir+Blocs::Types::url[i]).c_str());
                pTexture_blocs[i] = SDL_CreateTextureFromSurface(pRenderer,Blocs::Types::sprites[i]);
            }


            std::cout << "SDL_Init(...);" << std::endl;
        }

    }

    Fenetre::~Fenetre() {

        for(auto text : pTexture_blocs)
            SDL_DestroyTexture(text);

        if(pWindow)
            SDL_DestroyWindow(pWindow);



        if(main_window && --nb_instances == 0) {
            for(auto s : Blocs::Types::sprites)
                SDL_FreeSurface(s);
            SDL_Quit();
            std::cout << "SDL_Quit();" << std::endl;
        }
    }


    void Fenetre::blitBloc(Blocs::Brique& b, int x, int y, SDL_Rect* crop_rect) {
        SDL_Rect dest;
        dest.w = Blocs::Types::dimX;
        dest.h = Blocs::Types::dimY;


        Blocs::PosBloc grille = b.get_grille();
        u8 size_x = grille.size_x;
        u8 size_y = grille.size_y;
        u8 type = b.get_type();


        for(std::unordered_set<u8>::iterator pos=grille.pos.begin(); pos!=grille.pos.end(); ++pos) {
            u8 j = *pos%size_x;
            u8 i = *pos/size_x;
            dest.x = x+j*dest.w;
            dest.y = y+i*dest.h;
            //b.set_position(dest.x/size_x,dest.y/size_y);
            SDL_RenderCopy(pRenderer,pTexture_blocs[type],crop_rect,&dest);
        }


    }

    void Fenetre::blitBlocExact(Blocs::Brique& b, int id_x, int id_y, SDL_Rect* crop_rect) {
        SDL_Rect dest;

        int w = Blocs::Types::dimX;
        int h = Blocs::Types::dimY;
        int x = id_x*w;
        int y = id_y*h;

        dest.h = h;
        dest.w = w;


        Blocs::PosBloc grille = b.get_grille();
        u8 size_x = grille.size_x;
        u8 size_y = grille.size_y;
        u8 type = b.get_type();




        for(std::unordered_set<u8>::iterator pos=grille.pos.begin(); pos!=grille.pos.end(); ++pos) {
            u8 j = *pos%size_x;
            u8 i = *pos/size_x;
            dest.x = x+j*w;
            dest.y = y+i*h;
            //b.set_position(dest.x/size_x,dest.y/size_y);
            SDL_RenderCopy(pRenderer,pTexture_blocs[type],crop_rect,&dest);
        }


    }

    void Fenetre::blitBloc(Blocs::Brique& b, SDL_Rect* crop_rect) {
        blitBlocExact(b,b.get_x(),b.get_y(),crop_rect);
    }



    void Fenetre::loop(Blocs::ListeBriques& briques, void (*boucle)(Blocs::ListeBriques&) ) {
        if(boucle!=nullptr) boucle(briques);
        else {
            SDL_Event event;
            bool continuer = true;

            int nb_blocs_x = width/Blocs::Types::dimX;
            int nb_blocs_y = height/Blocs::Types::dimY;


            int limX = nb_blocs_x;
            int limY = nb_blocs_y;


            Blocs::Brique* bloc = briques.front();
            bloc->deplacer_xExact(nb_blocs_x/2-1,limX,briques);
            bloc->deplacer_yExact(0,limY,briques);

            bool collision = false;

            while(continuer) {

                while(SDL_PollEvent(&event)) {

                    switch(event.type) {

                        case SDL_WINDOWEVENT: // fenêtre
                            if ( event.window.event == SDL_WINDOWEVENT_CLOSE )
                                continuer = false;
                            break;

                        case SDL_KEYDOWN:
                            switch(event.key.keysym.sym) {
                                case SDLK_SPACE:
                                    bloc->translate_yExact(1, limY, briques);
                                    collision = bloc->translate_yExact(1, limY, briques);
                                    break;
                                default:
                                    break;
                            }
                            break;



                        case SDL_KEYUP:
                            switch(event.key.keysym.sym) {
                                case SDLK_ESCAPE:
                                    continuer = false;
                                    break;
                                case SDLK_RIGHT:
                                    bloc->translate_xExact(1, limX, briques);
                                    //std::cout << "position du bloc : " << briques[0]->get_x() << ',' << briques[0]->get_y() << '\n';
                                    break;
                                case SDLK_LEFT:
                                    bloc->translate_xExact(-1, limX, briques);
                                    break;
                                case SDLK_UP:
                                    bloc->rotation_exacte(limX,limY,briques);
                                    break;
                                case SDLK_DOWN:
                                    bloc->tomber(limY,briques);
                                    collision = true;
                                    goto nouvelle_brique;
                                    break;
                                case SDLK_RETURN: {
                                    nouvelle_brique:
                                    bloc = briques.appendNew(Blocs::Types::distr(Blocs::Types::gen));
                                    int poslim = limX-1;
                                    while( poslim >=0 && !(bloc->deplacer_xExact(poslim,limX,briques)  && bloc->deplacer_yExact(0,limY,briques)) )
                                        --poslim;
                                    if(poslim < 0)
                                        continuer = false;
                                    std::cout << briques.size() << std::endl;
                                    break;
                                }
                                default:
                                    break;
                            }
                            break;
                        default:
                            break;

                    }

                    /*int ligne = nb_blocs_y-1;
                    while(ligne>=0) {*/

                        /// Insérer ici le code pour
                        /***
                        ligne = nb_blocs_y-1
                        nb_lignes_entamees = NOMBRE de lignes où il y a un (morceau de) bloc qui traine
                        TANT QUE ligne >= nb_lignes_entamees
                            TANT QUE ligne est remplie
                                POUR CHAQUE bloc qui touche la ligne
                                    SUPPRIMER la dernière ligne de sa grille
                                    FAIRE TOMBER le bloc d'un cran
                                SI tous les blocs les plus hauts (il peut y en avoir plusieurs) sont descendus
                                    --nb_lignes_entamees
                                ligne = nb_blocs_y-1
                        ***/
                       /* --ligne;
                    }*/


                }
                clear();
                for(auto b : briques)
                    blitBloc(*b,nullptr);
                update();
                pause(100);
            }


        }
    }



}
