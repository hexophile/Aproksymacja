#include <math.h>
#include <iostream>

using namespace std;

double getG(int n, double x[], int k, int j) {
	double temp = 0;
	for (int i = 0; i <= n; i++) {
		temp += pow(x[i], k + j);
	}
	return temp;
}

double getR(int n, double x[], int k, double f) {
	double temp = 0;
	for (int i = 0; i <= n; i++) {
		temp += pow(x[i], k) * f;
	}
	return temp;
}

double APROX(double x[], double y[], int m, int n) {
	
	double *macierzR = new double[m];
	double **macierzG = new double*[m];
	
	for (int i = 0; i < m; i++) {
		macierzG[i] = new double[m + 1];
	}

	for ( int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			macierzG[i][j] = getG(n, x, i, j );
		}
		macierzR[i] = getR(n, x, i, y[i]);//sin(x[i]));
	}

	for (int i = 0; i < m; i++) {
		macierzG[i][m] = macierzR[i];
	} // Sklejamy macierz R z G uzywajac dodatkowej kolumny zadeklarowanej za pomoc¹ [m+1]
	
	// Ga³s \/
	int a, b, c, n, suma;
	
	for (a = 0; a < n - 1; a++)
	{
		for (b = a + 1; b < n; b++)
		{
			for (c = a; c<n + 1; c++)
				macierzG[b][c] = macierzG[b][c] - (macierzG[b][a] / macierzG[a][a] ) *macierzG[a][c];
		}
	}

	macierzR[n - 1] = macierzG[n - 1][n] / macierzG[n - 1][n - 1];
	
	for (b = n - 2; b >= 0; b--)
	{
		suma = 0;
		for (c = b + 1; c < n; c++)
		{
			suma += (macierzG[b][c] * macierzR[c]);
			macierzR[b] = (macierzG[b][n] - suma) / macierzG[b][b];
		}
	}
}

int main() {

}