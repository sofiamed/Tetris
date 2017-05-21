#include "Blocs.hpp"

int main(int argc, char* argv[]) {
	
	std::cout << "Guten Tag" << std::endl;
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
	
	
	return 0;
}