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
