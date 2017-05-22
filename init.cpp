#include "Blocs.hpp"
#include "Fenetre.hpp"


int main(int argc, char** argv) {

	std::cout << "Debug grilles" << std::endl;
	Blocs::Point p1;
	p1.print_grille();
	Blocs::Ligne p2;
	p2.print_grille();
	Blocs::Cube p3;
	p3.print_grille();
	Blocs::Droite p4;
	p4.print_grille();
	Blocs::Gauche p5;
	p5.print_grille();
	std::cout << "Debug grilles après rotation" << std::endl;
	p1.rotation();
	p1.print_grille();
	p2.rotation();
	p2.print_grille();
	p3.rotation();
	p3.print_grille();
	p4.rotation();
	p4.print_grille();
	p5.rotation();
	p5.print_grille();

	std::cout << "Guten Tag" << std::endl;
	std::cout << "Ich bin Berliner" << std::endl;


	Graphique::Fenetre fen("Titre 1", 800, 600, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, false);
	Graphique::Fenetre fen2("Titre 2");




	return 0;
}
