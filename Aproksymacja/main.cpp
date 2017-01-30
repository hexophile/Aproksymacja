#include <math.h>
#include <iostream>

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

//tablica punktow, ilosc punktow, zakres punktow
double *rownoodlegleX(int n, double &a, double &b)
{
	if ((a<b) && (n> 0)) {
		double *tab = new double[n + 1];

		for (int i = 0; i <= n; i++)
		{
			tab[i] = r_xp(n, i, a, b);
		}
		return tab;
	}
	else {
		string exc;
		if (n <= 0) {
			exc = "InsufficientNodesAmountException: n <= 0; at ";
		}
		else if (a >= b) {
			exc = "InsufficientRangeException: parameter float &a <= float &b; at ";
		}
		else {
			exc = "GeneralException; at ";
		}
	}
}

double funkcjaAproksymowana(double x)
{
	return sin(abs(x));        //1 typ funkcji jest to funkcja testowa
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

double *APROX(double x[], double y[], double wyniki[], int m, int n) {

	double *macierzR = new double[m];
	double **macierzG = new double*[m];

	for (int i = 0; i < m; i++) {
		macierzG[i] = new double[m + 1];
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			macierzG[i][j] = getG(n, x, i, j);
			cout << macierzG[i][j] << " ";
		}
		cout << endl;
		macierzR[i] = getR(n, x, i, y);//sin(x[i]));
	}

	for (int i = 0; i < m; i++) {
		macierzG[i][m] = macierzR[i];
	} // Sklejamy macierz R z G uzywajac dodatkowej kolumny zadeklarowanej za pomoc¹ [m+1]

	  // Ga³s \/
	int a, b, c;
	double suma;
	for (a = 0; a < m - 1; a++)
	{
		for (b = a + 1; b < m; b++)
		{
			for (c = a; c<m + 1; c++)
				macierzG[b][c] = macierzG[b][c] - (macierzG[b][a] / macierzG[a][a]) *macierzG[a][c];
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
	cout << "Podaj ilos punktow" << endl;
	cin >> n;
	cout << "Podaj stopien wielomianu" << endl;
	cin >> m;
	cout << "Podaj zakres aproksymacji" << endl;
	cin >> a >> b;
}
int main()
{
	int n, m;
	double a, b;
	double *x;
	double *y;
	double *wyniki;
	pobierzDane(n, m, a, b);
	wyniki = new double[m];
	y = new double[n];
	x = rownoodlegleX(n - 1, a, b);
	for (int i = 0; i < n; i++)
	{
		y[i] = funkcjaAproksymowana(x[i]);
	}
	for (int i = 0; i < n; i++)
	{
		cout << i << " " << x[i] << " " << y[i] << endl;
	}
	wyniki = APROX(x, y, wyniki, m, n);
	for (int i = 0; i < m; i++)
	{
		cout << wyniki[i] << endl;
	}
	cout << bladAProksymacji(wyniki, x, y, n, m);
	delete[] x;
	delete[] y;
	delete[] wyniki;
	cin.ignore();
	getchar();
	return 0;
}