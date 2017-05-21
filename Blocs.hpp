#ifndef include_Blocs
#define include_Blocs

#include "defs.hpp"


namespace Blocs {

	namespace Types {
			enum { Point=0, Ligne=1, Cube=2, Droite=3, Gauche=4 };
			static const std::string url[] = { "Point.png", "Ligne.png", "Cube.png", "Droite.png", "Gauche.png" };
			static const std::string names[] = { "Point", "Ligne", "Cube", "Droite", "Gauche" };
			static const std::string basedir = "TetrisRes/img/tiles/Blocs/";
	}

	
	typedef struct _Coord {	
		int x,y;
		int h,w;
		
		_Coord() : x(0),y(0),h(32),w(32) {}
		
		
	} Coord; 
	
	typedef struct _PosBloc {
		u8 size_x, size_y; // définit la grille de placement. Sérialise un carré de taille size_x*size_y
		std::unordered_set<u8> pos; // liste des positions où se trouve un bloc (point) dans la grille sérialisée
		
		/*** ATTENTION size_x est le nombre de colonnes et pas le nombre de lignes !!! ***/
		
		
		_PosBloc() : size_x(1),size_y(1) {}
		
		
		
	} PosBloc;

	
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
			
			
		private:
			inline void set_url() { url = Types::basedir + Types::url[type]; }
		
		protected:
			PosBloc grille; // la grille qui décrit la brique comme un ensemble de blocs
			Coord coord; // coordonnée supérieure gauche en prenant (0,0) en haut à gauche de la fenêtre
			u8 type; // id
			std::string url; // texture du bloc de base : initialisée par le constructeur en fonction de 'type'
		
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
			
			inline void rotation() { std::swap(grille.size_x,grille.size_y); }	
		
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
