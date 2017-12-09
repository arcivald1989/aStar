#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct Element
{
	int status;
	int droga;
	double heurystyka;
	double suma;
	int kierunekRodzica; // 1-prawo, 2-dó³, 3-lewo, 4-góra
};

int main()
{
	const int wsplYstart = 0;
	const int wsplXstart = 0;
	const int wsplYend = 19;
	const int wsplXend = 19;
	ifstream plik;
	plik.open("grid.txt");
	if (plik.good())
	{
		cout << "Plik otwarty!" << endl;
	}

	Element mapa[20][20]; // Wczytanie z pliku mapy
	bool sciezka[20][20] = { false };
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			plik >> mapa[i][j].status;
			mapa[i][j].heurystyka = sqrt((i - wsplYend)*(i - wsplYend) + (j - wsplXend)*(j - wsplXend));
		}
	}
	plik.close();
	for (int i = 0; i < 20; i++) // Pokazuje mape
	{
		for (int j = 0; j < 20; j++)
		{
			cout << mapa[i][j].status << " ";
		}
		cout << endl;
	}

	cout << endl;

	// 0,0 -> 19,19
	// kolejnosc przeszukiwania (prawo, dó³, lewo, góra)
	// w przypadku równych sum wybieramy element o ni¿szej heurystyce, jeœli równe pierwszy znaleziony

	mapa[wsplYstart][wsplXstart].status = 1;
	mapa[wsplYstart][wsplXstart].droga = 0;
	mapa[wsplYstart][wsplXstart].suma = mapa[wsplYstart][wsplXstart].droga + mapa[wsplYstart][wsplXstart].heurystyka;
	bool znalezionoKoniec = false;
	int minX, minY;
	while (!znalezionoKoniec)
	{
		double min = 10000000;

		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (mapa[i][j].status == 1)
				{
					if (min > mapa[i][j].suma || (min == mapa[i][j].suma && mapa[minY][minX].heurystyka > mapa[i][j].heurystyka)) {
						min = mapa[i][j].suma;
						minY = i;
						minX = j;
					}
				}
			}
		}

		if (min == 10000000) {
			cout << "Nie znaleziono sciezki." << endl;
			system("pause");
			return 0;
		}

		if (minY == wsplYend && minX == wsplXend) {
			znalezionoKoniec = true;
			break;
		}

		mapa[minY][minX].status = 2;

		if (minX <= 18) {
			if (mapa[minY][minX + 1].status == 0 || (mapa[minY][minX + 1].status == 1 && mapa[minY][minX + 1].droga > mapa[minY][minX].droga + 1)) {
				mapa[minY][minX + 1].status = 1;
				mapa[minY][minX + 1].droga = mapa[minY][minX].droga + 1;
				mapa[minY][minX + 1].suma = mapa[minY][minX + 1].droga + mapa[minY][minX + 1].heurystyka;
				mapa[minY][minX + 1].kierunekRodzica = 3;
			}
		}
		if (minY <= 18) {
			if (mapa[minY + 1][minX].status == 0 || (mapa[minY + 1][minX].status == 1 && mapa[minY + 1][minX].droga > mapa[minY][minX].droga + 1)) {
				mapa[minY + 1][minX].status = 1;
				mapa[minY + 1][minX].droga = mapa[minY][minX].droga + 1;
				mapa[minY + 1][minX].suma = mapa[minY + 1][minX].droga + mapa[minY + 1][minX].heurystyka;
				mapa[minY + 1][minX].kierunekRodzica = 4;
			}
		}
		if (minX >= 1) {
			if (mapa[minY][minX - 1].status == 0 || (mapa[minY][minX - 1].status == 1 && mapa[minY][minX - 1].droga > mapa[minY][minX].droga + 1)) {
				mapa[minY][minX - 1].status = 1;
				mapa[minY][minX - 1].droga = mapa[minY][minX].droga + 1;
				mapa[minY][minX - 1].suma = mapa[minY][minX - 1].droga + mapa[minY][minX - 1].heurystyka;
				mapa[minY][minX - 1].kierunekRodzica = 1;
			}
		}
		if (minY >= 1) {
			if (mapa[minY - 1][minX].status == 0 || (mapa[minY - 1][minX].status == 1 && mapa[minY - 1][minX].droga > mapa[minY][minX].droga + 1)) {
				mapa[minY - 1][minX].status = 1;
				mapa[minY - 1][minX].droga = mapa[minY][minX].droga + 1;
				mapa[minY - 1][minX].suma = mapa[minY - 1][minX].droga + mapa[minY - 1][minX].heurystyka;
				mapa[minY - 1][minX].kierunekRodzica = 2;
			}
		}
	}

	while (!(minX == wsplXstart && minY == wsplYstart)) {
		int biezacyX = minX;
		int biezacyY = minY;
		sciezka[biezacyY][biezacyX] = true;
		mapa[biezacyY][biezacyX].status = 3;

		if (mapa[biezacyY][biezacyX].kierunekRodzica == 1) { minX++; }
		if (mapa[biezacyY][biezacyX].kierunekRodzica == 2) { minY++; }
		if (mapa[biezacyY][biezacyX].kierunekRodzica == 3) { minX--; }
		if (mapa[biezacyY][biezacyX].kierunekRodzica == 4) { minY--; }
	}
	sciezka[minY][minX] = true;
	mapa[minY][minX].status = 3;

	for (int i = 0; i < 20; i++) // Pokazuje mape
	{
		for (int j = 0; j < 20; j++)
		{
			cout << mapa[i][j].status << " ";
		}
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < 20; i++) // Pokazuje mape
	{
		for (int j = 0; j < 20; j++)
		{
			cout << (sciezka[i][j] == true ? "x" : (mapa[i][j].status == 5 ? "#" : " ")) << " ";
		}
		cout << endl;
	}
	system("pause");
	return 0;
}