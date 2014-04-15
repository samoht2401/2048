// 2048.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

// Gère l'affichage
void display(int tab[][4])
{
	for (int y = 0; y < 4; y++)
	{
		printf("_____________________\n");
		printf("|    |    |    |    |\n");

		string s = "";
		for (int x = 0; x < 4; x++)
		{
			int val = tab[x][y];
			if (val == 0)
				s += "|    ";
			else if (val < 10)
			{
				s += "|  ";
				s += to_string(val);
				s += " ";
			}
			else if (val < 100)
			{
				s += "| ";
				s += to_string(val);
				s += " ";
			}
			else if (val < 1000)
			{
				s += "| ";
				s += to_string(val);
			}
			else if (val < 10000)
			{
				s += "|";
				s += to_string(val);
			}
		}
		s += "|\n";
		printf(s.c_str());

		printf("|    |    |    |    |\n");
	}
	printf("_____________________\n");
};

int _tmain(int argc, _TCHAR* argv[])
{
	int tableau[4][4] = { { 1, 5, 7, 15 }, // pour [X,Y] : X vertical, Y horizontale
						{ 2, 1, 15, 0 }, // !!! La table est donc transposé (symétrique à la diagonale haut-gauche, bas-droite)
						{ 3, 15, 1, 0 },
						{ 15, 0, 0, 1 } };

	display(tableau);

	scanf_s("%d");

	return 0;
}

