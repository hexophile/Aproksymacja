#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;

void pobierzX(double *x, int n)
{
	cout << "podaj X" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> x[i];
	}
}

// Szacowanie wartoœci punktu 'x' w równoodleg³ym wybieraniu punktów na zadanym przedziale
double r_xp(int &n, int &i, double &a, double &b)
{
	return a + i * ((b - a) / n);
}

// Tablica 'n' równoodleg³ych punktów na zadanym przedziale <a; b>
double *rownoodlegleX(int n, double &a, double &b)
{
	if ((a < b) && (n > 0)) {
		double *tab = new double[n + 1];

		for (int i = 0; i <= n; i++)
		{
			tab[i] = r_xp(n, i, a, b);
		}
		return tab;
	}
	else {
		return NULL; // error
	}
}

double funkcjaAproksymowana(double x)
{
	return sin(x)*sin(2 * x);
}

double getG(int n, double x[], int k, int j) {
	double temp = 0;
	for (int i = 0; i < n; i++) {
		temp += pow(x[i], (k + j));
	}
	return temp;
}

double getR(int n, double x[], int k, double *f) {
	double temp = 0;
	for (int i = 0; i < n; i++) {
		temp += pow(x[i], k) * f[i];
	}
	return temp;
}

// g³ówna funkcja, wyznacza wêz³y funkcji aproksymuj¹cej
double *APROX(double x[], double y[], int m, int n) {

	double *macierzR = new double[m];
	double **macierzG = new double*[m];

	for (int i = 0; i < m; i++) {
		macierzG[i] = new double[m + 1];
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			macierzG[i][j] = getG(n, x, i, j);
	//		cout << macierzG[i][j] << " ";	
		}
	//	cout << endl;
		macierzR[i] = getR(n, x, i, y);
	}

	for (int i = 0; i < m; i++) {
		macierzG[i][m] = macierzR[i];
	} // Sklejamy macierz R z G uzywajac dodatkowej kolumny zadeklarowanej za pomoc¹ [m+1]

	// Gauss \/
	int a, b, c;
	double suma;

	for (a = 0; a < m - 1; a++)
	{
		for (b = a + 1; b < m; b++)
		{
			for (c = a; c < m + 1; c++)
				macierzG[b][c] = macierzG[b][c] - (macierzG[b][a] / macierzG[a][a]) * macierzG[a][c];
		}
	}

	macierzR[m - 1] = macierzG[m - 1][m] / macierzG[m - 1][m - 1];

	for (b = m - 2; b >= 0; b--)
	{
		suma = 0;
		for (c = b + 1; c < m; c++)
		{
			suma += (macierzG[b][c] * macierzR[c]);
			macierzR[b] = (macierzG[b][m] - suma) / macierzG[b][b];
		}
	}

	for (int i = 0; i < m; i++) {
		//wyniki[i] = macierzR[i];
		delete[] macierzG[i];
	}
	delete[] macierzG;
	return macierzR;
}

double *wartosciFunkcjiAproksymujacej(double *x, double *APRX, int n, int m)
{
	double *wyniki = new double[n];

	for (int i = 0; i < n; i++)
	{
		wyniki[i] = 0;

		for (int j = 0; j < m; j++)
		{
			wyniki[i] += APRX[j] * pow(x[i], j);
		}
	}

	return wyniki;
}

//tabela A to wyniki gausa
double bladAProksymacji(double *a, double *x, double *f, int n, int m)
{
	double sumaPotegowa = 0;
	double suma = 0;
	for (int i = 0; i < n; i++)    //np 0 do 49
	{
		for (int j = 0; j < m; j++)
		{
			suma += a[j] * pow(x[i], j) - f[i];
		}
		sumaPotegowa += pow(suma, 2);
		suma = 0;
	}
	sumaPotegowa /= n + 1;
	sumaPotegowa = sqrt(sumaPotegowa);
	return sumaPotegowa;
}

void pobierzDane(int &n, int &m, double &a, double &b)
{
	cout << "Podaj ilosc punktow: ";
	cin >> n;
	cout << "Podaj stopien wielomianu: ";
	cin >> m;
	cout << "Podaj przedzial aproksymacji: ";
	cin >> a >> b;
}

int main()
{
	int n, m;
	double a, b, *x, *y, *wyniki, *wynikiAprx;

	pobierzDane(n, m, a, b);
	y = new double[n];
	x = rownoodlegleX(n - 1, a, b);

	ofstream plikWynikowy, plikBledow;
	plikWynikowy.open("wyniki.txt");
	plikBledow.open("bledy.txt");

	plikWynikowy << n << " " << m << " " << a << " " << b << endl;

	plikWynikowy << "____f(x)____" << endl;

	for (int i = 0; i < n; i++)
	{
		y[i] = funkcjaAproksymowana(x[i]);
		plikWynikowy << y[i] << endl;
	}

	plikWynikowy << "____x____" << endl;

	for (int i = 0; i < n; i++)
	{
	//	cout << i << " " << x[i] << " " << y[i] << endl;
		plikWynikowy << x[i] << endl;
	}

	plikWynikowy << "____wêz³y____" << endl;

	wyniki = APROX(x, y, m, n);

	for (int i = 0; i < m; i++)
	{
	//	cout << wyniki[i] << endl;
		plikWynikowy << wyniki[i] << endl;
	};

	plikWynikowy << "____L(x)____" << endl;

	wynikiAprx = wartosciFunkcjiAproksymujacej(x, wyniki, n, m);

	for (int i = 0; i < n; i++)
	{
		//	cout << i << " " << x[i] << " " << y[i] << endl;
		plikWynikowy << wynikiAprx[i] << endl;
	}

	plikWynikowy << endl << bladAProksymacji(wyniki, x, y, n, m);

	delete[] x;
	delete[] y;
	delete[] wyniki;

	/*
	Pêtla zapisuj¹ca b³êdy aproksymacji do pliku, stopnie wielomianu od 1 do 20
	*/
	for (m = 1; m <= 20; m++)
	{
		y = new double[n];
		x = rownoodlegleX(n - 1, a, b);

		for (int i = 0; i < n; i++)
		{
			y[i] = funkcjaAproksymowana(x[i]);
		}

		wyniki = APROX(x, y, m, n);

		plikBledow << m << " " << bladAProksymacji(wyniki, x, y, n, m) << endl;

		delete[] x;
		delete[] y;
		delete[] wyniki;
	}

	plikWynikowy.close();
	plikBledow.close();

	cin.ignore();
	getchar();

	return 0;
}