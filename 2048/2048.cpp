// 2048.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <cstdlib>
#include <Windows.h>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

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
	int tableau[4][4] = { { 0, 0, 0, 0 }, // pour [X,Y] : X vertical, Y horizontale
	{ 0, 0, 0, 0 }, // !!! La table est donc transposé (symétrique à la diagonale haut-gauche, bas-droite)
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } };

	bool exit = false;
	bool needUpdate = true;

	do
	{
		if (GetKeyState(VK_LEFT) < 0) // Left Arrow is pressed
		{
			for (int x = 1; x < 4; x++)
			{
				for (int y = 0; y < 4; y++)
				{
					int val = tableau[x][y];
					if (val != 0)
					{
						for (int i = 1; i <= x; i++)
						{
							int other = tableau[x - i][y];
							if (other != 0)
							{
								if (val == other)
								{
									tableau[x][y] = 0;
									tableau[x - i][y] = val * 2;
									needUpdate = true;
								}
								else if (i > 1)
								{
									tableau[x][y] = 0;
									tableau[x - i + 1][y] = val;
									needUpdate = true;
								}
								break;
							}
							else if (x - i == 0)
							{
								tableau[x][y] = 0;
								tableau[0][y] = val;
								needUpdate = true;
							}
						}
					}
				}
			}
		}
		if (GetKeyState(VK_RIGHT) < 0) // Right Arrow is pressed
		{
			for (int x = 3; x >= 0; x--)
			{
				for (int y = 0; y < 4; y++)
				{
					int val = tableau[x][y];
					if (val != 0)
					{
						for (int i = 1; i <= 4 - x; i++)
						{
							int other = tableau[x + i][y];
							if (other != 0)
							{
								if (val == other)
								{
									tableau[x][y] = 0;
									tableau[x + i][y] = val * 2;
									needUpdate = true;
								}
								else if (i > 1)
								{
									tableau[x][y] = 0;
									tableau[x + i - 1][y] = val;
									needUpdate = true;
								}
								break;
							}
							else if (x + i == 3)
							{
								tableau[x][y] = 0;
								tableau[3][y] = val;
								needUpdate = true;
							}
						}
					}
				}
			}
		}
		if (GetKeyState(VK_UP) < 0) // Up Arrow is pressed
		{
			for (int y = 0; y < 4; y++)
			{
				for (int x = 1; x < 4; x++)
				{
					int val = tableau[x][y];
					if (val != 0)
					{
						for (int i = 1; i <= y; i++)
						{
							int other = tableau[x][y - i];
							if (other != 0)
							{
								if (val == other)
								{
									tableau[x][y] = 0;
									tableau[x][y - i] = val * 2;
									needUpdate = true;
								}
								else if (i > 1)
								{
									tableau[x][y] = 0;
									tableau[x][y - i + 1] = val;
									needUpdate = true;
								}
								break;
							}
							else if (y - i == 0)
							{
								tableau[x][y] = 0;
								tableau[x][0] = val;
								needUpdate = true;
							}
						}
					}
				}
			}
		}
		if (GetKeyState(VK_DOWN) < 0) // Down Arrow is pressed
		{
			for (int y = 3; y >= 0; y--)
			{
				for (int x = 1; x < 4; x++)
				{
					int val = tableau[x][y];
					if (val != 0)
					{
						for (int i = 1; i <= 4 - y; i++)
						{
							int other = tableau[x][y + i];
							if (other != 0)
							{
								if (val == other)
								{
									tableau[x][y] = 0;
									tableau[x][y + i] = val * 2;
									needUpdate = true;
								}
								else if (i > 1)
								{
									tableau[x][y] = 0;
									tableau[x][y + i - 1] = val;
									needUpdate = true;
								}
								break;
							}
							else if (y + i == 3)
							{
								tableau[x][y] = 0;
								tableau[x][3] = val;
								needUpdate = true;
							}
						}
					}
				}
			}
		}

		if (needUpdate)
		{
			system("cls");
			display(tableau);
			needUpdate = false;
		}

		Sleep(50);

	} while (!exit);

	return 0;
}

