// 2048.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <cstdlib>
#include <stdlib.h>
#include <Windows.h>


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

// Gère l'affichage
void displayMenu()
{
	printf("==========Menu==========\n");
	printf("1. Play\n2. Scores\n3. Quit\n");
};

void displayScore(int score)
{
	printf_s("==========Best Score==========\n");
	printf_s("%d", score);
};

void displayGame(int tab[][4], int score)
{
	printf("_____________________\n");
	printf("|    |    |    |    |    Score : %d\n", score);
	for (int y = 0; y < 4; y++)
	{
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
		printf("_____________________\n");
		if (y != 3)
			printf("|    |    |    |    |\n");
	}
};

void getNewNumber(int tab[][4])
{
	//Randomize :
	int val = 0;
	int r = rand() % 100;
	if (r < 80)
		val = 2;
	else
		val = 4;
	for (int i = 500; i > 0; i--)
	{
		int r = rand() % 16;
		if (tab[r % 4][r / 4] == 0)
		{
			tab[r % 4][r / 4] = val;
			break;
		}
	}
}

int readScore()
{
	FILE* pfile;
	fopen_s(&pfile, "scores.txt", "r");
	if (pfile != NULL)
	{
		int savedVal;
		fscanf_s(pfile, "%d", &savedVal);
		fclose(pfile);
		return savedVal;
	}
	return 0;
}

bool isInMenu = true;
bool isWin = false;

int _tmain(int argc, _TCHAR* argv[])
{
	int tableau[4][4] = { { 0, 0, 0, 0 }, // pour [X,Y] : X vertical, Y horizontale
	{ 0, 0, 0, 0 }, // !!! La table est donc transposé (symétrique à la diagonale haut-gauche, bas-droite)
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } };

	bool exit = false;
	bool needUpdate = true;
	bool isLost = false;
	bool isInScore = false;
	int cooldown = 0;
	int score = 0;

	srand(2401);

	do
	{
		if (GetKeyState(VK_ESCAPE) < 0)
		{
			isLost = false;
			isWin = false;
			isInMenu = true;
			isInScore = false;
			needUpdate = true;
		}
		if (isLost)
		{
			if (GetKeyState(VK_RETURN) < 0)
			{
				isLost = false;
				isWin = false;
				isInMenu = true;
				needUpdate = true;
			}
		}
		// Code du menu
		else if (isInMenu)
		{
			if (GetKeyState(0x31) < 0 || GetKeyState(VK_NUMPAD1) < 0) // 1.Play
			{
				isInMenu = false;
				needUpdate = true;
				for (int x = 0; x < 4; x++)
				for (int y = 0; y < 4; y++)
					tableau[x][y] = 0;
				getNewNumber(tableau);
			}
			if (GetKeyState(0x32) < 0 || GetKeyState(VK_NUMPAD2) < 0) // 2.Scores
			{
				isInMenu = false;
				isInScore = true;
				needUpdate = true;
				score = readScore();
				
			}
			if (GetKeyState(0x33) < 0 || GetKeyState(VK_NUMPAD3) < 0) // 3.Quit
			{
				exit = true;
			}
		}
		// Code du jeu
		else
		{
			if (cooldown == 0)
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
											score += val * 2;
											needUpdate = true;
											if (val * 2 == 2048)
											{
												needUpdate = true;
												isWin = true;

											}

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
					for (int x = 2; x >= 0; x--)
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
											score += val * 2;
											needUpdate = true;
											if (val * 2 == 2048)
											{
												needUpdate = true;
												isWin = true;

											}

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
					for (int y = 1; y < 4; y++)
					{
						for (int x = 0; x < 4; x++)
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
											score += val * 2;
											needUpdate = true;
											if (val * 2 == 2048)
											{
												needUpdate = true;
												isWin = true;

											}

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
					for (int y = 2; y >= 0; y--)
					{
						for (int x = 0; x < 4; x++)
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
											score += val * 2;
											needUpdate = true;
											if (val * 2 == 2048)
											{
												needUpdate = true;
												isWin = true;

											}

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
			}

			if (needUpdate) // Quelque chose a bougé
			{
				getNewNumber(tableau);

				//Tab plein ?
				bool isThere0 = false;
				for (int x = 0; x < 4; x++)
				{
					for (int y = 0; y < 4; y++)
					{
						if (tableau[x][y] == 0)
						{
							isThere0 = true;
							break;
						}
					}
					if (isThere0)
						break;
				}
				if (!isThere0)
				{
					//Combine posible ?
					bool canCombine = false;
					for (int i = 0; i < 8; i++)
					{
						int pair = i / 2 % 2; // Pair == 0 // Impair == 1
						int x = (i % 2) * 2 + pair;
						int y = i / 2;

						int val = tableau[x][y];
						if ((x>0 && val == tableau[x - 1][y]) || (x<3 && val == tableau[x + 1][y]) ||
							(y>0 && val == tableau[x][y - 1]) || (y < 3 && val == tableau[x][y + 1]))
						{
							canCombine = true;
							break;
						}
					}

					if (!canCombine)
						isLost = true;

					cooldown = 250;
				}
			}
		}

		if (needUpdate)
		{
			system("cls");

			if (isInMenu)
				displayMenu();
			else if (isInScore)
				displayScore(score);

			else
				displayGame(tableau, score);

			if (isLost)
			{
				printf("Vous avez perdu\n");// Rajouter ici les scores de fin
				FILE* pfile;
				fopen_s(&pfile,"scores.txt", "r");
				if (pfile != NULL)
				{
					int savedVal;
					fscanf_s(pfile, "%d", &savedVal);
					fclose(pfile);
					pfile = NULL;

					if (score > savedVal)
					{
						fopen_s(&pfile, "scores.txt", "w");
						
						if (pfile != NULL)
						{
							fprintf_s(pfile, "%d", score);
							fclose(pfile);
						}
					}
				}
			}
			if (isWin)
				printf("Vous avez gagne");

			needUpdate = false;
		}
		Sleep(50);

		cooldown -= 50;
		if (cooldown < 0)
			cooldown = 0;

	} while (!exit);

	return 0;
}

