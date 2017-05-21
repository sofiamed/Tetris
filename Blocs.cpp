#include "Blocs.hpp"

namespace Blocs {
	
	/// Class Brique
	Brique::Brique(u8 type) : type(type) { set_url(); }
	Brique::~Brique() {}
	
	
	void Brique::print_grille(bool verbose) {
				
		int sx = grille.size_x;
		int sy = grille.size_y;
		auto it_fin = grille.pos.end();
			
		std::cout << "Type de brique : " << Types::names[type] << '\n';
				
		if(verbose)				
			std::cout << "x : bloc present\n";
			
		for(int i=0; i!=sy; ++i) {
			for(int j=0; j!=sx; ++j)
				if(grille.pos.find(j+i*sx) != it_fin)
					std::cout << "x";
				else
					std::cout << " ";
			std::cout << '\n';					
		}
	}	
	

	/// Class Point
	Point::Point() : Brique(Types::Point) {
		grille.pos.insert(0);
		std::cout << url << std::endl; 
	}
	Point::~Point() {}

	
	/// Class Ligne
	Ligne::Ligne() : Brique(Types::Ligne) {
		grille.size_x = 5;
		for(int i=0; i!=5; ++i) 
			grille.pos.insert(i);
		std::cout << url << std::endl;
	}
	Ligne::~Ligne() {}
	

	/// Class Cube
	Cube::Cube() : Brique(Types::Cube) {
		grille.size_x = 2;
		grille.size_y = 2;
		for(int i=0; i!=4; ++i) 
			grille.pos.insert(i);
		std::cout << url << std::endl;
	}
	Cube::~Cube() {}
	

	/// Class Droite
	Droite::Droite() : Brique(Types::Droite) {
		grille.size_x = 3;
		grille.size_y = 2;
		for(int i=1; i!=5; ++i)
			grille.pos.insert(i);		
		std::cout << url << std::endl;
	}
	Droite::~Droite() {}
	
	void Droite::rotation() {
		std::swap(grille.size_x,grille.size_y);
		grille.pos.clear();
		grille.pos.insert(0);
		grille.pos.insert(2);
		grille.pos.insert(3);
		grille.pos.insert(5);
	}
	

	/// Class Gauche
	Gauche::Gauche() : Brique(Types::Gauche) {
		grille.size_x = 3;
		grille.size_y = 2;
		grille.pos.insert(0);
		grille.pos.insert(1);
		grille.pos.insert(4);
		grille.pos.insert(5);
		std::cout << url << std::endl;
	}
	Gauche::~Gauche() {}
	
	void Gauche::rotation() {
		std::swap(grille.size_x,grille.size_y);
		grille.pos.clear();
		for(int i=1; i!=5; ++i)
			grille.pos.insert(i);
	}
	
	
}