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
	int k, i, j;
	double suma;

	for (k = 0; k < m - 1; k++)
	{
		for (i = k + 1; i < m; i++)
		{
			for (j = k; j < m + 1; j++)
			{
				macierzG[i][j] = macierzG[i][j] - ((macierzG[i][k] * macierzG[k][j]) / macierzG[k][k]);
			}
		}
	}

	macierzR[m - 1] = macierzG[m - 1][m] / macierzG[m - 1][m - 1];

	for (i = m - 2; i >= 0; i--)
	{
		suma = 0;
		for (j = i + 1; j < m; j++)
		{
			suma += (macierzG[i][j] * macierzR[j]);
			macierzR[i] = (macierzG[i][m] - suma) / macierzG[i][i];
		}
	}

	for (int i = 0; i < m; i++) {
		//wyniki[i] = macierzR[i];
		delete[] macierzG[i];
	}
	delete[] macierzG;
	return macierzR;
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

	ofstream plikWynikowy;
	plikWynikowy.open("wyniki.txt");

	plikWynikowy << "n " << n << endl;
	plikWynikowy << "m " << m << endl;
	plikWynikowy << "a " << a << endl;
	plikWynikowy << "b " << b << endl;

	plikWynikowy << "f(x)" << endl;

	for (int i = 0; i < n; i++)
	{
		y[i] = funkcjaAproksymowana(x[i]);
		plikWynikowy << y[i] << endl;
	}

	plikWynikowy << "x" << endl;

	for (int i = 0; i < n; i++)
	{
	//	cout << i << " " << x[i] << " " << y[i] << endl;
		plikWynikowy << x[i] << endl;
	}

	plikWynikowy << "wêz³y" << endl;

	wyniki = APROX(x, y, m, n);

	for (int i = 0; i < m; i++)
	{
	//	cout << wyniki[i] << endl;
		plikWynikowy << wyniki[i] << endl;
	};

	plikWynikowy << "B³¹d: " << endl << bladAProksymacji(wyniki, x, y, n, m);

	delete[] x;
	delete[] y;
	delete[] wyniki;
	
	cout << "Gotowe.";

	plikWynikowy.close();

	cin.ignore();
	getchar();

	return 0;
}