/*
int main() {
	int a, i, j, n, s;
	int macierz[10][10], x[10];
	double p;
	
	for (a = 0; a<n - 1; a++)
	{
		for (i = a + 1; i<n; i++)
		{
			p = macierz[i][a] / macierz[a][a];
			for (j = a; j<n + 1; j++)
				macierz[i][j] = macierz[i][j] - p*macierz[a][j];
		}
	}

x[n - 1] = macierz[n - 1][n] / macierz[n - 1][n - 1];
for (i = n - 2; i >= 0; i--)
{
	s = 0;
	for (j = i + 1; j<n; j++)
	{
		s += (macierz[i][j] * x[j]);
		x[i] = (macierz[i][n] - s) / macierz[i][i];
	}
}
*/


//	wynikiAprx = wartosciFunkcjiAproksymujacej(x, wyniki, n, m);

/*
Pêtla zapisuj¹ca b³êdy aproksymacji do pliku, stopnie wielomianu od 1 do 20
*//*
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
*/