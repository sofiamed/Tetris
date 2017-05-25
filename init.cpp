#include "Fenetre.hpp"


int main(int argc, char** argv) {


    const int nb_blocs_x = 10;
    const int nb_blocs_y = 15;

    const u16 x = Blocs::Types::dimX;
    const u16 y = Blocs::Types::dimY;


    Graphique::Fenetre fen("Tetris tests", nb_blocs_x*x, nb_blocs_y*y, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);



	std::cout << "Debug grilles" << std::endl;
	Blocs::Point p1;
	p1.print_grille();
	fen.blitBloc(p1,0,0);

	Blocs::Ligne p2;
	p2.print_grille();
	fen.blitBloc(p2, x+10,0);

	Blocs::Cube p3;
	p3.print_grille();
	fen.blitBloc(p3,6*x+20,0);

	Blocs::Droite p4;
	p4.print_grille();
	fen.blitBloc(p4,8*x+30,0);

	Blocs::Gauche p5;
	p5.print_grille();
	fen.blitBloc(p5,11*x+40,0);


	std::cout << "Debug grilles après rotation" << std::endl;
	p1.rotation();
	p1.print_grille();
	fen.blitBloc(p1,0,y+10);

	p2.rotation();
	p2.print_grille();
	fen.blitBloc(p2,3*x+10,y+10);

	p3.rotation();
	p3.print_grille();
	fen.blitBloc(p3,6*x+20,2*y+10);

	p4.rotation();
	p4.print_grille();
	fen.blitBloc(p4,8*x+30,2*y+10);

	p5.rotation();
	p5.print_grille();
	fen.blitBloc(p5,11*x+40,2*y+10);

	std::cout << "Guten Tag" << std::endl;
	std::cout << "Ich bin Berliner" << std::endl;

	fen.update();
	fen.pause(500);

    fen.clear();
    fen.blitBlocExact(p1, 10,3);

    fen.update();

    Blocs::ListeBriques briques;
    briques.append(&p4);


    fen.loop(briques);







	return 0;
}
