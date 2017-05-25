#include "Blocs.hpp"

namespace Blocs {

	/// Class Brique
	Brique::Brique(u8 type) : type(type), switch_rotate(false) { set_url(); }
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


	Brique* Brique::generate(u8 type) {
        switch(type) {
            case Types::Point:
                return (new Point());
                break;
            case Types::Ligne:
                return new Ligne;
                break;
            case Types::Cube:
                return new Cube;
                break;
            case Types::Droite:
                return new Droite;
                break;
            case Types::Gauche:
                return new Gauche;
                break;
            default:
                return nullptr;
                break;
        }
    }



	bool Brique::operator^(const Brique& b) {
            PosBloc grilleb = b.grille;
            std::unordered_set<std::pair<u8,u8> > pos;
            std::unordered_set<std::pair<u8,u8> > pos2;

            for(auto z : grille.pos) {
                pos.insert(std::pair<u8,u8>(z%grille.size_x+coord.x, z/grille.size_x+coord.y));
            }
            for(auto z : grilleb.pos) {
                pos2.insert(std::pair<u8,u8>(z%grilleb.size_x+b.coord.x,z/grilleb.size_x+b.coord.y));
            }

            for(auto z : pos2)
                if(pos.find(z) != pos.end())
                    return true;
            return false;
	}


	/// Class ListeBriques
	Brique* ListeBriques::appendNew(u8 type) {
        Brique* b = Brique::generate(type);
        briques.push_back(b);
        to_delete.push_back(b);
        return b;
    }

    ListeBriques::~ListeBriques() {
        for(auto z : to_delete)
            delete z;
        for(auto z : briques)
            z = nullptr;
        to_delete.clear();
        briques.clear();
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
		if(!switch_rotate) {
            grille.pos.insert(0);
            grille.pos.insert(2);
            grille.pos.insert(3);
            grille.pos.insert(5);
		}
		else
            for(int i=1; i!=5; ++i)
                grille.pos.insert(i);

		switch_rotate = !switch_rotate;
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

		if(!switch_rotate)
            for(int i=1; i!=5; ++i)
                grille.pos.insert(i);
        else {
            grille.pos.insert(0);
            grille.pos.insert(1);
            grille.pos.insert(4);
            grille.pos.insert(5);
        }
        switch_rotate = !switch_rotate;
	}


}
