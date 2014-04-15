// 2048.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int tab[4][4] = {{0,0,0,0}, // pour [X,Y] : X vertical, Y horizontale
					 {0,0,0,0}, // !!! La table est donc transposé (symétrique à la diagonale haut-gauche, bas-droite)
					 {0,0,0,0},
					 {0,0,0,0}};

	return 0;
}

