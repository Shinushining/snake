#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include <windows.h>

using namespace std;

int szerokosc, wysokosc, szybkosc;
int gora, dol, lewo, prawo;
char pole[35][35];
int wspolzednaXweza, wspolzednaYweza;
int wspolzednaXjedzenia, wspolzednaYjedzenia;
int dlugosc = 3;
int historiaWspolzednejX[10000], historiaWspolzednejY[10000];
int ile = 0;
int klawisz;
char kierunek = 'g';
char jed = 177;
char waz = 219;

void idzdoxy(int x, int y)
{
	HANDLE hCon;
	COORD dwPos;

	dwPos.X = x;
	dwPos.Y = y;

	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon, dwPos);
}

int blad(int& x)
{
	cout << "Mialo byc od 5 do 35!" << endl;
	cout << "masz ostatnia szanse!" << endl;
	cin >> x;
	if (x < 5 || x>35)
	{
		x = 20;
	}
	return 0;
}

int main()
{
	cout << "Podaj szerokosc planszy od 5 do 35" << endl;
	cin >> szerokosc;
	if (szerokosc < 5 || szerokosc>35)
	{
		blad(szerokosc);
	}
	cout << "Podaj wysokosc planszy od 5 do 35" << endl;
	cin >> wysokosc;
	if (wysokosc < 5 || wysokosc>35)
	{
		blad(wysokosc);
	}

	cout << "Podaj szybkosc od 1 do 10" << endl;
	cin >> szybkosc;
	if (szybkosc < 1)
	{
		szybkosc = 1;
	}
	else if (szybkosc > 10)
	{
		szybkosc = 10;
	}

	cout << "nacisnij klawisze ktorymi chcesz zagrac" << endl;
	cout << "GORA" << endl;
	gora = _getch();
	if (gora == 224)
	{
		gora += _getch();
	}
	if (gora == 0)
	{
		gora -= _getch();
	}

	cout << "DOL" << endl;
	dol = _getch();
	if (dol == 224)
	{
		dol += _getch();
	}
	if (dol == 0) {
		dol -= _getch();
	}

	cout << "LEWO" << endl;
	lewo = _getch();
	if (lewo == 224)
	{
		lewo += _getch();
	}
	if (lewo == 0)
	{
		lewo -= _getch();
	}
	cout << "PRAWO" << endl;

	prawo = _getch();
	if (prawo == 224)
	{
		prawo += _getch();
	}
	if (prawo == 0)
	{
		prawo -= _getch();
	}

	for (int i = 0; i < wysokosc; i++)
	{
		for (int j = 0; j < szerokosc; j++)
		{
			pole[j][i] = 'p';
		}
	}

	srand(time(NULL));

	wspolzednaXweza = rand() % szerokosc;
	wspolzednaYweza = rand() % wysokosc;

	pole[wspolzednaXweza][wspolzednaYweza] = 'w';

	do {
		wspolzednaXjedzenia = rand() % szerokosc;
		wspolzednaYjedzenia = rand() % wysokosc;
	} while (pole[wspolzednaXjedzenia][wspolzednaYjedzenia] != 'p');

	pole[wspolzednaXjedzenia][wspolzednaYjedzenia] = 'j';

	system("cls");

	for (;;)
	{

		ile++;
		historiaWspolzednejX[ile] = wspolzednaXweza;
		historiaWspolzednejY[ile] = wspolzednaYweza;

		idzdoxy(0, 0);

		for (int i = 0; i <= szerokosc; i++)
		{
			cout << "--";
		}



		for (int i = 0; i < wysokosc; i++)
		{
			cout << endl << "|";
			for (int j = 0; j < szerokosc; j++)
			{
				if (pole[j][i] == 'p')
				{
					cout << "  ";
				}
				if (pole[j][i] == 'w')
				{
					cout << waz << waz;
				}
				if (pole[j][i] == 'j')
				{
					cout << jed << jed;
				}
			}
			cout << "|";
		}
		cout << endl;
		for (int i = 0; i <= szerokosc; i++)
		{
			cout << "--";
		}

		Sleep(500 / szybkosc);
		if (_kbhit())
		{
			klawisz = _getch();
			if (klawisz < 0)
			{
				klawisz -= _getch();
			}
			if (klawisz > 224)
			{
				klawisz += _getch();
			}

			if (klawisz == gora && (kierunek == 'l' || kierunek == 'p'))
			{
				kierunek = 'g';
			}
			if (klawisz == dol && (kierunek == 'l' || kierunek == 'p'))
			{
				kierunek = 'd';
			}
			if (klawisz == lewo && (kierunek == 'g' || kierunek == 'd'))
			{
				kierunek = 'l';
			}
			if (klawisz == prawo && (kierunek == 'g' || kierunek == 'd'))
			{
				kierunek = 'p';
			}
		}


		if (kierunek == 'g')
		{
			wspolzednaYweza--;
		}
		if (kierunek == 'd')
		{
			wspolzednaYweza++;
		}
		if (kierunek == 'p')
		{
			wspolzednaXweza++;
		}
		if (kierunek == 'l')
		{
			wspolzednaXweza--;
		}

		if (pole[wspolzednaXweza][wspolzednaYweza] == 'w')
		{
			cout << endl << "KONIEC GRY      dlugosc - " << dlugosc + 1 << endl;
			break;
		}

		if (pole[wspolzednaXweza][wspolzednaYweza] == 'j')
		{
			dlugosc++;
			do {
				wspolzednaXjedzenia = rand() % szerokosc;
				wspolzednaYjedzenia = rand() % wysokosc;
			} while (pole[wspolzednaXjedzenia][wspolzednaYjedzenia] != 'p');
			pole[wspolzednaXjedzenia][wspolzednaYjedzenia] = 'j';
		}
		else
		{
			pole[historiaWspolzednejX[ile - dlugosc]][historiaWspolzednejY[ile - dlugosc]] = 'p';
		}

		if (wspolzednaXweza == szerokosc)
		{
			wspolzednaXweza = 0;
		}
		if (wspolzednaXweza == -1)
		{
			wspolzednaXweza = szerokosc - 1;
		}
		if (wspolzednaYweza == wysokosc)
		{
			wspolzednaYweza = 0;
		}
		if (wspolzednaYweza == -1)
		{
			wspolzednaYweza = wysokosc - 1;
		}
		pole[wspolzednaXweza][wspolzednaYweza] = 'w';



	}

	system("PAUSE");
	return 0;
}