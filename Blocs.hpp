#ifndef include_Blocs
#define include_Blocs

#include "defs.hpp"



namespace Blocs {

	namespace Types {
			enum { Point=0, Ligne=1, Cube=2, Droite=3, Gauche=4 };
			const unsigned nb_types = 5;
			static const std::string url[] = { "Point.png", "Ligne.png", "Cube.png", "Droite.png", "Gauche.png" };
			static const std::string names[] = { "Point", "Ligne", "Cube", "Droite", "Gauche" };
			static const std::string basedir = "TetrisRes/img/tiles/Blocs/";
			static std::vector<SDL_Surface*> sprites(nb_types,NULL);
			static const u16 dimX = 32; // largeur du bloc
			static const u16 dimY = 32; // hauteur du bloc
			static std::mt19937 gen(time(nullptr));
            static std::uniform_int_distribution<u8> distr(0,nb_types-1);
	}


	typedef struct _Coord {
		int x,y;
		int h,w;
		// position dans la grille globale (celle de la fenetre)

		_Coord() : x(0),y(0),h(Types::dimY),w(Types::dimX) {}


	} Coord;

	typedef struct _PosBloc {
		u8 size_x, size_y; // définit la grille de placement. Sérialise un carré de taille size_x*size_y
		std::unordered_set<u8> pos; // liste des positions où se trouve un bloc (point) dans la grille sérialisée

		/*** ATTENTION size_x est le nombre de colonnes et pas le nombre de lignes !!! ***/


		_PosBloc() : size_x(1),size_y(1) {}



	} PosBloc;

	class Brique;

	class ListeBriques {

        public:

            ListeBriques() {}
            ~ListeBriques();


            inline void append(Brique* b) { briques.push_front(b); }
            Brique* appendNew(u8 type=Types::Point);

            inline Brique* front() const { return briques.front(); }

            inline std::list<Brique*>::iterator begin() { return briques.begin(); }
            inline std::list<Brique*>::iterator end()   { return briques.end(); }
            inline u32 size() const { return briques.size(); }



        protected:
            std::list<Brique*> briques;
            std::list<Brique*> to_delete;


	};



	class Brique {

		public:
			Brique(u8 type=Types::Point);
			~Brique();
			virtual void rotation()=0; // change grille pour faire une rotation de pi/2 radians

			inline void set_position(int x, int y) { coord.x = x; coord.y = y; }
			inline void set_dims(int h, int w) { coord.h = h; coord.w = w; }

			inline void set_x(int x) { coord.x = x; }
			inline void set_y(int y) { coord.y = y; }
			inline void set_h(int h) { coord.h = h; }
			inline void set_w(int w) { coord.w = w; }

			void print_grille(bool verbose=false);

			inline u8 get_type() const { return type; }
			inline PosBloc get_grille() const { return grille; }
			inline int get_x() const { return coord.x; }
			inline int get_y() const { return coord.y; }


			bool translate_xExact(int offset, int limX, ListeBriques& briques) {
			    int backup = coord.x;
			    int z = coord.x+offset;
			    if(z>=0 && z+grille.size_x<=limX) {
                    coord.x = z;
                    for(auto B : briques) {
                        if(B == this)
                            continue;
                        if(this->operator^(*B)) {
                            coord.x = backup;
                            return false;
                        }
                    }
                    return true;
			    }
			    return false;
			}
			bool translate_yExact(int offset, int limY, ListeBriques& briques) {
			    int backup = coord.y;
			    int z = coord.y+offset;
			    if(z>=0 && z+grille.size_y<=limY) {
                    coord.y = z;
                    for(auto B : briques) {
                        if(B == this)
                            continue;
                        if(this->operator^(*B)) {
                            coord.y = backup;
                            return false;
                        }
                    }
                    return true;
			    }
			    return false;
			}

			bool deplacer_xExact(int dest, int limX, ListeBriques& briques) {
                int offset = dest-coord.x;
                return translate_xExact(offset,limX,briques);
			}
			bool deplacer_yExact(int dest, int limY, ListeBriques& briques) {
                int offset = dest-coord.y;
                return translate_yExact(offset,limY,briques);
			}

			bool rotation_exacte(int limX, int limY, ListeBriques& briques) {
                rotation();
                int zX = coord.x+grille.size_x;
                int zY = coord.y+grille.size_y;

                if(coord.x >= 0 && zX <= limX && coord.y >= 0 && zY <= limY) {

                    for(auto B : briques) {
                        if(B == this)
                            continue;
                        if(this->operator^(*B)) {
                            rotation();
                            return false;
                        }

                    }
                }
                else {
                    rotation();
                    return false;
                }
                return true;
			}

			inline void tomber(int limY, ListeBriques& briques) {
			    while(translate_yExact(1, limY, briques)) ;
			}



			bool operator^(const Brique& b); // true si collision


			static Brique* generate(u8 type=Blocs::Types::Point);

		private:
			inline void set_url() { url = Types::basedir + Types::url[type]; }

		protected:
			PosBloc grille; // la grille qui décrit la brique comme un ensemble de blocs
			Coord coord; // coordonnée (par bloc) supérieure gauche en prenant (0,0) en haut à gauche de la fenêtre
			u8 type;
			std::string url; // image stockée dans la texture du bloc de base : initialisée par le constructeur en fonction de 'type'
			bool switch_rotate;

	};


	class Point : public Brique {
		public:
			Point();
			~Point();
			inline void rotation() { }

	};


	class Ligne : public Brique  {
		public:
			Ligne();
			~Ligne();

			inline void rotation() { std::swap(grille.size_x,grille.size_y); switch_rotate = !switch_rotate; }

	};

	class Cube : public Brique  {
		public:
			Cube();
			~Cube();

			inline void rotation() {} // ne rien faire

	};

	class Droite : public Brique  {
		public:
			Droite();
			~Droite();

			void rotation(); // dans le .cpp
	};

	class Gauche : public Brique  {
		public:
			Gauche();
			~Gauche();

			void rotation(); // dans le .cpp
	};

}



#endif // Namespace Blocs. Classes Bloc,Brique,Point,Ligne,Cube,Droite et Gauche. Enumeration Blocs::Types pour chacune d'elles
